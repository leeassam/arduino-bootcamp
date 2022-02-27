/*
Arduino Bootcamp

Stopwatch - Controlling a 4 Digit Segment Display - Part 1

This project demonstrates how to control a four digit seven segment display

by: Lee Assam

*/

//Pins for seven segment LED
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
//LED toggle Pins
int displayPins[] = {10, 11, 12, 13};
//Global values for display
int num1, num2, num3, num4;

//LED mappings for numbers
byte digits[10][8] = {
  //  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 0}, // 0
  { 0, 1, 1, 0, 0, 0, 0, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 0, 0, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0} //  9
};

void setup() {
  //Initialize seven segment pins as output from the Arduino
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
   //Pins for toggling LEDs
  for (int i = 0; i < 4; i++) {
    pinMode(displayPins[i], OUTPUT);
  }   
  //Turn Off Seven Segment Displays Initially
  for (int i = 0; i < 4; i++) {
    digitalWrite(displayPins[i], LOW);
  }    

  Serial.begin(9600);
  Serial.setTimeout(20);
  //Initialize values
  num1=0;
  num2=0;
  num3=0;
  num4=0;    
  Serial.println("Enter a number between 0 and 9999: ");
}


void loop() {
  static String input;
  if (Serial.available()) {
    //Read inoput string
    input = Serial.readString();
    //Get first digit
    char ch1 = input.charAt(0);
    //get second digit
    char ch2 = input.charAt(1);
    //get third digit
    char ch3 = input.charAt(2);    
    //get fourth digit
    char ch4 = input.charAt(3);        
    //convert to integers
    num1 = ch1 - '0';
    num2 = ch2 - '0';
    num3 = ch3 - '0';
    num4 = ch4 - '0';
  }
  //display digits
  updateDisplay(num1, num2, num3, num4);
}

void updateDisplay(int digit1, int digit2, int digit3, int digit4) {
//Toggle displays on an off and show each digit separately 
//Show only first digit 
  digitalWrite(displayPins[0], HIGH);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], LOW);
  setSegments(digit1);
  delay(2);
//Show only second digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], HIGH);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], LOW);  
  setSegments(digit2);
  delay(2);
//Show only third digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], HIGH);
  digitalWrite(displayPins[3], LOW);  
  setSegments(digit3);
  delay(2);
//Show only fourth digit   
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], LOW);
  digitalWrite(displayPins[2], LOW);
  digitalWrite(displayPins[3], HIGH);  
  setSegments(digit4);
  delay(2);    
}

void setSegments(int n) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], !digits[n][i]);
  }
}

