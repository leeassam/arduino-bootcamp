/*
Arduino Bootcamp

- Operating a Stopwatch with a 4 Digit Segment Display - Part 3

  This project will create a stopwatch with a dual seven segment display.
  It uses the 74HC595 shift register to control led display with only 3 pins from the Arudino
  
  by: Lee Assam
*/
#include <StopWatch.h>
#include <Bounce2.h>
//Pins for seven segment LED
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
//LED toggle Pins
int displayPins[] = {10, 11, 12, 13};
//Global values for display
int num1, num2, num3, num4;
int displayValue = 0;

//Start/Stop/Reset Button
#define buttonPin 5
// Instantiate Bounce object
Bounce debouncer = Bounce();
unsigned long buttonPressTimeStamp;

//LED mappings for numbers
byte digits[10][8] = {
  //  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 0}, // 0
  { 0, 1, 1, 0, 0, 0, 0, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 0, 0, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0} //  9
};

//Values for seven segment display
byte leds = 0;
byte digitVals[10];

//Shift Register Pins
//Pin connected to latch pin (RCLK) of 74HC595
#define latchPin  8
//Pin connected to clock pin (SRCLK) of 74HC595
#define clockPin 7
//Pin connected to data pin (SER) of 74HC595
#define dataPin 6

//Create stopwatch objects
StopWatch SW_secs(StopWatch::SECONDS);
StopWatch SW_millis; // MILLIS (default)

void setup() {
  //Initialize seven segment pins as output from the Arduino
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  //Pins for toggling LEDs
  for (int i=0; i<4; i++) {
    pinMode(displayPins[i], OUTPUT);
  }
  //Turn Off Seven Segment Displays Initially
  for (int i=0; i<4; i++) {
    digitalWrite(displayPins[i], LOW);
  }  
  
  Serial.begin(9600);
  //Enable internal pullup on button pin
  pinMode(buttonPin, INPUT_PULLUP);
  // After setting up the buttons, setup the Bounce instance :
  debouncer.attach(buttonPin);
  debouncer.interval(5); // interval in ms
  //Initialize values
  num1=0;
  num2=0;
  num3=0;
  num4=0;    
//Shift Register Pins
  pinMode (latchPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  //set byte array
  setDigitVals();  
  //Starting the stopwatch
  displayValue = 0;
}


void loop() {
  //checking for start/stop
  // Update the Bounce instance :
  debouncer.update();
  //If a fall occurred, the switch was pressed
  if ( debouncer.fell()  ) {
    buttonPressTimeStamp = millis();
    if (SW_secs.isRunning()) {
      //stop if running
      SW_secs.stop();
      SW_millis.stop();
    } else {
      //start since it was previously stopped
      SW_secs.start();
      SW_millis.start();
    }
  }

  if ( debouncer.rose()) {
    //checking for long button press to reset
    if (millis() - buttonPressTimeStamp > 2000) {
      startOver(false);
    }

  }

  //Only incrementing display after every second
  if ( SW_secs.elapsed() == (displayValue + 1)) {
    displayValue++;
    //100 min - 60 x 100
    if (displayValue == 6000) {
      //resetting after reaching 100 mins
      startOver(true);
    }
    //get first digit
    //10's minutes
    num1 = (displayValue / 60) / 10;
    //get second digit
    //minutes
    num2 = (displayValue / 60) % 10;
    //get third digit
    //10's seconds
    num3 = (displayValue % 60) / 10;   
    //get fourth digit
    //seconds
    num4 = (displayValue % 60) % 10;    
  }
  //update the seven segment display
    updateDisplay(num1, num2, num3, num4);
}

void updateDisplay(int digit1, int digit2, int digit3, int digit4) {
//Toggle displays on an off and show each digit separately 
//Show only first digit 
  digitalWrite(displayPins[0], HIGH);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], LOW);
  setSegments(digit1);
  delay(2);
//Show only second digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], HIGH);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], LOW);  
  setSegments(digit2);
  delay(2);
//Show only third digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], HIGH);
  digitalWrite(displayPins[3], LOW);  
  setSegments(digit3);
  delay(2);
//Show only fourth digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], HIGH);  
  setSegments(digit4);
  delay(2);    
}

//Todo: Modify to take a boolean to determine if the decimal point should be set
void setSegments(int n) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digitVals[n]);
  digitalWrite(latchPin, HIGH);  
}

//start over the stop watch
void startOver(bool startCount) {
  //reset stopwatches
  displayValue = 0;
  SW_secs.reset();
  SW_millis.reset();
  if (startCount) {
    //automatically restart
    SW_secs.start();
    SW_millis.start();
  } else {
    //do not restart and set display to 0
    num1 = 0;
    num2 = 0;
    num3 = 0;
    num4 = 0;
  }
}

//convert digits bit array into actual array of bytes needed for the shift register
void setDigitVals() {
  for ( int j = 0; j < 10; j++ ) {
    byte leds = 0;
    for (int i = 0; i<8; i++) {
    if (digits[j][i] == 0) {
      bitSet(leds, 7-i);
    } else {
      bitClear(leds, 7-i);
    }
  }
  digitVals[j] = leds;
  }
}
