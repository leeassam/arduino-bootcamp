/*
  Arduino Bootcamp

  - Pan Tilt Assembly Control - Demo of taking readings from the Wii Nunchuk

 * ArduinoNunchukDemo.ino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 * 
 * by: Lee Assam
 *
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

ArduinoNunchuk nunchuk = ArduinoNunchuk();

// SCL is connected to A5
// SDA is connected to A4
// +3.3V connected to +
// GND connected to -

void setup()
{
  Serial.begin(BAUDRATE);
  nunchuk.init();
}

void loop()
{
  nunchuk.update();

  Serial.print("X: ");
  Serial.print(nunchuk.analogX, DEC);
  Serial.print(' ');
  Serial.print("Y: ");  
  Serial.print(nunchuk.analogY, DEC);
  Serial.print(' ');
  Serial.print("Acc X: ");
  Serial.print(nunchuk.accelX, DEC);
  Serial.print(' ');
  Serial.print("Acc Y: ");
  Serial.print(nunchuk.accelY, DEC);
  Serial.print(' ');
  Serial.print("Acc Z: ");
  Serial.print(nunchuk.accelZ, DEC);
  Serial.print(' ');
  Serial.print("Z btn: ");
  Serial.print(nunchuk.zButton, DEC);
  Serial.print(' ');
  Serial.print("C btn: ");
  Serial.println(nunchuk.cButton, DEC);
}
