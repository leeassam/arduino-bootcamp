/*
Arduino Bootcamp

  - Simple LED Switch Circuit

This project demonstrates how a push  button switch can be used to turn an LED ON/OFF

by: Lee Assam

*/
 
//Set the LED Pin constant globally
//The LED is connected to Pin 8 of the Arduino
#define LEDPin 8
//Connected to one pin of the switch
#define ButtonPin 7

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED Pin as an output.
  pinMode(LEDPin, OUTPUT);
  //set the Button Pin as an input
  pinMode(ButtonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(ButtonPin) == LOW) {
    digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
  digitalWrite(LEDPin, LOW);    // turn the LED off by making the voltage LOW
  }
}
