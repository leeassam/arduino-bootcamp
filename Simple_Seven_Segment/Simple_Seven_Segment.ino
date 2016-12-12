/*
Seven Segment
=========================

This project demonstrates how to set up a seven segment display

*/
  int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

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
    for (int i = 0; i < 8; i++) {
      pinMode(segmentPins[i], OUTPUT);
      digitalWrite(segmentPins[i], HIGH);
    }
    Serial.begin(9600);
    Serial.println("Enter a number between 0 and 9: ");
  }

  void loop() {
    if (Serial.available()) {
      char ch = Serial.read();
      if (ch >= '0' && ch <= '9') {
        int num = ch - '0';
        updateDisplay(num);
      }
    }
  }

  void updateDisplay(int value) {
    setSegments(value);
  }

  void setSegments(int n) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], digits[n][i]);
    }
  }

