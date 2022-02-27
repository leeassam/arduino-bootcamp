/*
Arduino Bootcamp

- Piezo Buzzer Circuit

This project demonstrates how a push  button switch can be used to sound a piezo buzer

by: Lee Assam

*/
//Set the LED Pin constant globally
//The +ve buzzer pin is connected to pin 9 of the Arduino
#define buzzer 9
//Connected to grounded resistor of switch
#define ButtonPin 7

// the setup function runs once when you press reset or power the board
void setup() {
  //set the Button Pin as an input
  pinMode(ButtonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(ButtonPin) == HIGH) {
    tone(buzzer, 2000);   // sound the buzzer
  } else {
    noTone(buzzer);    // turn the buzzer off
  }
}
