/*
Arduino Bootcamp

- Digital Dice

  This project uses a seven segment display to create a digital dice

by: Lee Assam

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

byte spinDigits [6][8] = {
  //  a  b  c  d  e  f  g
  { 1, 0, 0, 0, 0, 0, 0, 0}, // a
  { 0, 1, 0, 0, 0, 0, 0, 0}, // b
  { 0, 0, 1, 0, 0, 0, 0, 0}, // c
  { 0, 0, 0, 1, 0, 0, 0, 0}, // d
  { 0, 0, 0, 0, 1, 0, 0, 0}, // e
  { 0, 0, 0, 0, 0, 1, 0, 0}  // f
};

#define buttonPin 9

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
  //set up swich
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    //roll dice
    spin();
    roll();
    delay(500);
  }
}

void roll() {
  int roll = random(1, 7);
  updateDisplay(roll);
}

void spin() {
  for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], spinDigits[j][i]);
    }
    delay(250);
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

