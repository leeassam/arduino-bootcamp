/*
Arduino Bootcamp

- LED Reaction Game - Part 2

This project demonstrates a reaction game with LEDs. The objective is to push the switch when the Red LED is lit

by: Lee Assam

*/
 

//Set the LED Pin constants globally
//The Green LED is connected to Pin 8 of the Arduino
#define greenLED 8
//The Red LED is connected to Pin 9 of the Arduino
#define redLED 9
//The Yellow LED is connected to Pin 10 of the Arduino
#define yellowLED 10
//random set of times for the LEDs to be lit
int timesOn[] = {100, 250, 400, 500};
//random delays between LEDs being lit
int delayTimes[] = {250, 500, 1000, 1500};

//Declaring volatile variables so they can be accessed/changed within the ISR
volatile boolean redLEDLit = false;
volatile boolean isWinner = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LEDs Pins as outputs.
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  //creating interrupt
  attachInterrupt(0, checkWinner, FALLING);
  //Turn off LEDs
  turnOffLEDs();
}

// the loop function runs over and over again forever
void loop() {
  //randomly determine which LED is to be lit
  int LEDToLight = random(1,4);
  //determine a random time the LED should be on
  int periodLEDIsLit = timesOn[random(4)];
  //light the respective LED
  lightLED(LEDToLight, periodLEDIsLit);
  //turn off the LEDs
  turnOffLEDs();
  //delay for a random time after LEDs are turned off - makes game unpredictable  
  int delayTime = delayTimes[random(4)];
  delay(delayTime);
  //check winner flag for a winner
  if (isWinner) {
    isWinner = false;
    //there was a winner so display the winning LED light sequence
    winner(); 
  }
}

//Light an LED for a specificed duration in millis
void lightLED(int led, int duration) {
  switch (led) {
  case 1: //green
    digitalWrite(greenLED, HIGH);
    break;
  case 2: //red
    redLEDLit = true;
    digitalWrite(redLED, HIGH);
    break;    
  case 3: //yellow
    digitalWrite(yellowLED, HIGH);
    break;    
  default:
    break;
  } 
  //wait the duration
  delay(duration);
  //reset redLEDLit flag
  redLEDLit = false;
}

void turnOffLEDs() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
}

//Flashes 3 times in succession to indicate a win
void winner() {
  for (int i=0; i<3; i++) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    delay(250);    
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW); 
    delay(250);    
  }
  delay(3000);
}

//ISR to determine if the button was pressed while the Red LED was lit
void checkWinner() {
  if (redLEDLit) {
    //set winner flag
    isWinner = true;
  }    
}


