/*
Arduino Bootcamp

- Simple LED Circuit

This project demonstrates how an LED can be controlled by the Arduino

by: Lee Assam

*/

//Set the LED Pin constant globally
//The LED is connected to Pin 8 of the Arduino
#define LEDPin 8


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED Pin as an output.
  pinMode(LEDPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //Turn the LED On
  digitalWrite(LEDPin, HIGH);
  //Wait 1 second
  delay(1000);
  //Turn the LED Off
  digitalWrite(LEDPin, LOW);
  //Wait 1 second
  delay(1000);
}
