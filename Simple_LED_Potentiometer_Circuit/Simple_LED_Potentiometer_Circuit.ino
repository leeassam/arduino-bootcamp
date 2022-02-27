/*
Arduino Bootcamp

  - Simple LED Potentiometer Circuit

This project demonstrates how the brightness of an LED can be controlled by a potentiometer using pulse width modulation

by: Lee Assam

*/
//Set the LED Pin constant globally
//The LED is connected to Pin 9 of the Arduino
#define LEDPin 9
//Connect A0 to middle pot pin
#define potPin A0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED Pin as an output.
  pinMode(LEDPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //Read the voltage at the pot pin and convert to value between 0 and 255
  int reading = map(analogRead(potPin),0,1023,0,255);
  //Send PWM output to LED
  analogWrite(LEDPin, reading);
  delay(10);
}
