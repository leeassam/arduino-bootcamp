/*
Arduino Bootcamp

- Joystick Operation

  This sketch shows the basic operation of a Thumb Joystick
  The joystick outputs two analog voltages (VERT and HORIZ), and one digital signal (SEL) for the pushbutton.

  Connections to joystick (change if you use different pins):

by: Lee Assam

*/

const int VERT = A0; // analog
const int HORIZ = A1; // analog
const int SEL = A2; // digital

// Also connect the joystick VCC to Arduino 5V, and joystick GND to Arduino GND.

// This sketch outputs serial data at 9600 baud (open Serial Monitor to view).

void setup()
{
  // make the SEL line an input
  pinMode(SEL,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL,HIGH);

  // set up serial port for output
  Serial.begin(9600);
}

void loop() 
{
  int vertical, horizontal, select;
  
  // read all values from the joystick
  
  vertical = analogRead(VERT); // will be 0-1023
  horizontal = analogRead(HORIZ); // will be 0-1023
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed
  
  // print out the values
  
  Serial.print("vertical: ");
  Serial.print(vertical,DEC);
  Serial.print(" horizontal: ");
  Serial.print(horizontal,DEC);
  Serial.print(" select: ");
  if(select == HIGH)
    Serial.println("not pressed");
  else
    Serial.println("PRESSED!");
}  
