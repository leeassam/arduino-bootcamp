/*
Arduino Bootcamp

- Controlling a CPU Fan - User Input Control - Part 1

This project demonstrates how a CPU Fan can be controlled with the Arduino. 
The objective is to drive a higher load with an external power source and use a transistor as a switch
The user will be asked to enter the fan speed

by: Lee Assam

*/

#define motorPin 11

void setup() {
  //define motor pin as an output
  pinMode(motorPin, OUTPUT);
  //initially turn off the fan
  analogWrite(motorPin, 0);
  Serial.begin(9600);
  //Display instructions
  Serial.println("Enter a number between 0 and 9: ");
}

void loop() {
 if (Serial.available()) {
  //Get the input from the user
  char ch = Serial.read();
  if (ch>= '0' && ch <= '9') {
    int speed = ch - '0'; 
    //Set the appropriate fan speed
    analogWrite(motorPin, map(speed, 0, 9, 0, 255));
  }
 }   
}

