/*
Arduino Bootcamp

- Infrared Repeater

  This project creates an infrared repeater that can store and record three IR signals.
  To record a signal, aim the IR remote at the circuit, press the remote button you want to record, then press the circuit button you want to associate with that signal.
  You can play back a signal from the circuit by pushing the button which was associated with that stored signal.
  You can store/record and playback three signals even when power is removed from the circuit. The recordings are stored in EEPROM.

  Original IR logic:
  Version 0.11 September, 2009
  Copyright 2009 Ken Shirriff
  http://arcfn.com
  
  
  created 10/30/2016
  modified 10/30/2016
  by: Lee Assam
*/

#include <IRremote.h>
#include <EEPROM.h>
#include <Bounce2.h>

#define RECV_PIN 11
#define STATUS_PIN 13

#define buttonPin1 4
#define buttonPin2 5
#define buttonPin3 6

// Instantiate Bounce objects
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

//Storage for recordings
struct recording {
  int codeType; //The type of code
  unsigned long codeValue; // The code value if not raw
  unsigned int rawCodes[RAWBUF]; // The durations if raw
  int codeLen; // The length of the code
  int toggle; // The RC5/6 toggle state
} currentRecording, rec1, rec2, rec3;

boolean recordingComplete;
int lastButtonState;
int buttonState = 1;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(STATUS_PIN, OUTPUT);
  //Enable internal pullup on button pin
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  // After setting up the buttons, setup the Bounce instance :
  debouncer1.attach(buttonPin1);
  debouncer1.interval(20); // interval in ms
  debouncer2.attach(buttonPin2);
  debouncer2.interval(20); // interval in ms
  debouncer3.attach(buttonPin3);
  debouncer3.interval(20); // interval in ms
  recordingComplete = true;
  //Retrieve stored recordings
  getStoredRecordings();
}



// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results) {
  currentRecording = {0};
  currentRecording.codeType = results->decode_type;
  int count = results->rawlen;
  if (currentRecording.codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    currentRecording.codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= currentRecording.codeLen; i++) {
      if (i % 2) {
        // Mark
        currentRecording.rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        currentRecording.rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(currentRecording.rawCodes[i - 1], DEC);
    }
    Serial.println("");
  }
  else {
    if (currentRecording.codeType == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    }
    else if (currentRecording.codeType == SONY) {
      Serial.print("Received SONY: ");
    }
    else if (currentRecording.codeType == PANASONIC) {
      Serial.print("Received PANASONIC: ");
    }
    else if (currentRecording.codeType == JVC) {
      Serial.print("Received JVC: ");
    }
    else if (currentRecording.codeType == RC5) {
      Serial.print("Received RC5: ");
    }
    else if (currentRecording.codeType == RC6) {
      Serial.print("Received RC6: ");
    }
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(currentRecording.codeType, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    currentRecording.codeValue = results->value;
    currentRecording.codeLen = results->bits;
  }
  recordingComplete = false;
}

void sendCode(int repeat, recording *rec) {

  Serial.println("Inside send code");

  Serial.println("Got here");
  if (rec->codeType == NEC) {
    if (repeat) {
      irsend.sendNEC(REPEAT, rec->codeLen);
      Serial.println("Sent NEC repeat");
    }
    else {
      irsend.sendNEC(rec->codeValue, rec->codeLen);
      Serial.print("Sent NEC ");
      Serial.println(rec->codeValue, HEX);
    }
  }
  else if (rec->codeType == SONY) {
    irsend.sendSony(rec->codeValue, rec->codeLen);
    Serial.print("Sent Sony ");
    Serial.println(rec->codeValue, HEX);
  }
  else if (rec->codeType == PANASONIC) {
    irsend.sendPanasonic(rec->codeValue, rec->codeLen);
    Serial.print("Sent Panasonic");
    Serial.println(rec->codeValue, HEX);
  }
  else if (rec->codeType == JVC) {
    irsend.sendPanasonic(rec->codeValue, rec->codeLen);
    Serial.print("Sent JVC");
    Serial.println(rec->codeValue, HEX);
  }
  else if (rec->codeType == RC5 || rec->codeType == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      rec->toggle = 1 - rec->toggle;
    }
    // Put the toggle bit into the code to send
    rec->codeValue = rec->codeValue & ~(1 << (rec->codeLen - 1));
    rec->codeValue = rec->codeValue | (rec->toggle << (rec->codeLen - 1));
    if (rec->codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(rec->codeValue, HEX);
      irsend.sendRC5(rec->codeValue, rec->codeLen);
    }
    else {
      irsend.sendRC6(rec->codeValue, rec->codeLen);
      Serial.print("Sent RC6 ");
      Serial.println(rec->codeValue, HEX);
    }
  }
  else if (rec->codeType == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    irsend.sendRaw(rec->rawCodes, rec->codeLen, 38);
    Serial.println("Sent raw");
  }
}


void loop() {

  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();

   int button1State = debouncer1.read();
   int button2State = debouncer2.read();
   int button3State = debouncer3.read();

  if (recordingComplete == false) {
    //Serial.println("Recording complete is false");
    //save and assign the signal to a button if it was pressed
    //checking for pressed buttons
    if (debouncer1.fell()) {
      //##TODO -- Consolidate in a function
    //if (button1State == LOW) {
      //associaite with button 1
      associateWithButton(1);
    } else if (debouncer2.fell()) {
      //} else if (button2State == LOW) {
      //associaite with button 2
      associateWithButton(2);
    } else if (debouncer3.fell()) {
      //} else if (button3State == LOW) {
      //associaite with button 3
      associateWithButton(3);
    }
    
  } else {
    //transmit the signal if a button was pressed
    //checking for pressed buttons
    //if (debouncer1.fell()) {    
    if (button1State == LOW) {  
      //transmit signal associated with button 1
        transmitForButton(1);       
    //} else if (debouncer2.fell()) {
    } else if (button2State == LOW) {
      //transmit signal associated with button 2
        transmitForButton(2);          
    //} else if (debouncer3.fell()) {
    } else if (button3State == LOW) {
      //transmit signal associated with button 3
        transmitForButton(3);      
    }
  }

  //checking for depressed buttons
  if (debouncer1.rose() || debouncer2.rose() || debouncer2.rose()) {
    buttonState = 1;
    Serial.println("Released");
    irrecv.enableIRIn(); // Re-enable receiver
    Serial.println("Released----here");
    delay(100);
  }  

  //checking to see if an IR signal is being sent to be stored
  if (irrecv.decode(&results)) {
    digitalWrite(STATUS_PIN, HIGH);
    //Reset variable
    //initializeRecording(&currentRecording);
    storeCode(&results);
    irrecv.resume(); // resume receiver
    digitalWrite(STATUS_PIN, LOW);
  }

  lastButtonState = buttonState;
}

void transmitForButton(int button) {
      buttonState = 0;
      //transmit signal associated with button 1
        Serial.print("Recording complete: ");
        Serial.println(recordingComplete);
        Serial.print("Pressed, sending button ");
        Serial.println(button);
        digitalWrite(STATUS_PIN, HIGH);
        if (button == 1) {
          sendCode(lastButtonState == buttonState, &rec1);
        } else if (button == 2) {
          sendCode(lastButtonState == buttonState, &rec2);          
        } else if (button ==3) {
          sendCode(lastButtonState == buttonState, &rec3);
        }
        digitalWrite(STATUS_PIN, LOW);
        delay(50); // Wait a bit between retransmissions  
}

void associateWithButton(int button) {
        Serial.print("Storing code for button ");
        Serial.println(button);
      buttonState = 0;
      if (button ==1) {
        rec1 = currentRecording;
      } else if (button ==2) {
        rec2 = currentRecording;
      } else if (button ==3) {
        rec3 = currentRecording;
      }
      
      setStoredRecordings(); 
      recordingComplete = true;
      delay(2000);
}

void initializeRecording(recording *rec) {
  rec = {0}; //Initializing to null
  //rec->codeType = -1; // The type of code
  rec->toggle = 0; // The RC5/6 toggle state
}

void getStoredRecordings() {
  EEPROM.get(0,rec1);
  EEPROM.get(300,rec2);
  EEPROM.get(600,rec3);
}

void setStoredRecordings() {
  EEPROM.put(0, rec1);
  EEPROM.put(300, rec2);
  EEPROM.put(600, rec3);
}

