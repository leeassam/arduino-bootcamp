/*
  Arduino Bootcamp

  - Pan Tilt Servo Nunchuk

  This project demonstrates how a Wii Nunchuk can be used to control a pan-tilt assembly

  by: Lee Assam

*/

#include <Servo.h>
#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

//Create servo objects
Servo myservo1;  
Servo myservo2;

//Define Nunchuck
// SCL is connected to A5
// SDA is connected to A4
// +3.3V connected to +
// GND connected to -
ArduinoNunchuk nunchuk = ArduinoNunchuk();
int pos1 = 90;    // variable to store the servo position
int pos2 = 90;

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 10 to the servo object
  Serial.begin(BAUDRATE);
  nunchuk.init();
  //center servos
    myservo1.write(pos1);  
    myservo2.write(pos2);
    delay(15);
}

void loop() {

  nunchuk.update();

  //x 24- left to 212- right
  //y 220-up to 38-down

  pos1 = map (nunchuk.analogX, 212, 24, 0, 180);
  pos2 = map (nunchuk.analogY, 38, 220, 0, 180);
  
  myservo1.write(pos1);  // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);  // tell servo to go to position in variable 'pos'
    delay(15);  

  
}

