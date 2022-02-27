/*
  Arduino Bootcamp

  - Joystick LED Matrix Operation

  This project demonstrates how the movement of a joystick can be mapped and displayed on an LED Matrix

  by: Lee Assam

*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int matrix_x, matrix_y;
Max72xxPanel matrix = Max72xxPanel(pinCS, 1, 1);

const int VERT = 0; // analog
const int HORIZ = 1; // analog
const int SEL = A2; // digital

// Also connect the joystick VCC to Arduino 5V, and joystick GND to Arduino GND.

// This sketch outputs serial data at 9600 baud (open Serial Monitor to view).

void setup()
{
  // make the SEL line an input
  pinMode(SEL, INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL, HIGH);

  matrix.setIntensity(5);

  // set up serial port for output
  Serial.begin(115200);
}

void loop()
{
  int vertical, horizontal, select;

  // read all values from the joystick

  vertical = analogRead(VERT); // will be 0-1023
  horizontal = analogRead(HORIZ); // will be 0-1023
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed

  matrix_y = map(vertical, 5, 1018, 7, 0); // Maps values in the range
  // 0 to 1023 to the range
  // 7 to 0
  matrix_x = map(horizontal, 1018, 5, 0, 7); // Maps values in the range
  // 0 to 1023 to the range
  // 0 to 7

  matrix.fillScreen(0);   //Clear the screen
  //display new x and y values
  Serial.print("x: ");
  Serial.println(matrix_x);
  Serial.print("y: ");
  Serial.println(matrix_y);

  matrix.drawPixel(matrix_x, matrix_y, HIGH);
  matrix.write();         // Send bitmap to display
  delay(10);

  // print out the values

  Serial.print("vertical: ");
  Serial.print(vertical, DEC);
  Serial.print(" horizontal: ");
  Serial.print(horizontal, DEC);
  Serial.print(" select: ");
  //Determine if joystick was pressed
  if (select == HIGH)
    Serial.println("not pressed");
  else
    Serial.println("PRESSED!");
}
