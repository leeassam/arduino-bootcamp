//Looping


void setup() {

  //If- Else Loop
  if (digitalRead(buttonPin) == LOW) {
    //Turn on LED
    digitalWrite(LEDPin, HIGH);
  } else {

    digitalWrite(LEDPin, LOW);
  }


  if (state == 0) {
    //fan is set to lowest setting
    analogWrite(motorPin, map(3, 0, 9, 0, 255));
    state = 1;
  } else if (state == 1) {
    //fan is set to medium setting
    analogWrite(motorPin, map(6, 0, 9, 0, 255));
    state = 2;
  } else if (state == 2) {
    //fan is set to highest setting
    analogWrite(motorPin, map(9, 0, 9, 0, 255));
    state = 3;
  } else if (state == 3) {
    //fan is shut off
    analogWrite(motorPin, 0);
    state = 0;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

