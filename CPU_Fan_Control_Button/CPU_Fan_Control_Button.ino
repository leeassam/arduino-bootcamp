/*
Arduino Bootcamp

Controlling a CPU Fan - Button Speed Control - Part 2

This project demonstrates how a CPU Fan can be controlled with the Arduino. 
The objective is to use a button to adjust the fan speed.

by: Lee Assam

*/
#define motorPin 11
#define buttonPin 5
int state = 0;

void setup() {
  //Setting the motor pin as output
  pinMode(motorPin, OUTPUT);
  //Using the internal pullup resistor on the button pin
  pinMode(buttonPin, INPUT_PULLUP);
  //Initiallly turn off the fan
  analogWrite(motorPin, 0);
  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(buttonPin)==LOW) {
   if (state ==0) {
    //fan is set to lowest setting
    analogWrite(motorPin, map(3, 0, 9, 0, 255));
    state = 1;
   } else if (state ==1) {
    //fan is set to medium setting
    analogWrite(motorPin, map(6, 0, 9, 0, 255));
    state = 2;     
   } else if (state ==2) {
    //fan is set to highest setting
     analogWrite(motorPin, map(9, 0, 9, 0, 255));
     state = 3;
   } else if (state ==3) {
    //fan is shut off
     analogWrite(motorPin, 0);
     state = 0; 
   }
   delay(1000); //handle debouncing
  }
}

