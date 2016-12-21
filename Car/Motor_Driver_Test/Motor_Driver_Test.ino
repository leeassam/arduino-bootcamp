/*
  Arduino Bootcamp

  - Remote Controlled Car - Using a Motor Driver - Part 2

  This project demonstrates how a motor driver can be used to control two motors.
  It is a test program that cycles through the different directions of motor control.

  created 10/30/2016
  modified 10/30/2016
  by: Lee Assam

*/
// —————————————————————————  Motors
//Pins must be PWM to control motor speed on turns

int motor_left[] = {3, 5};
int motor_right[] = {9, 6};

int command = 0;
//PWM
int PWMSpeed = 125;

void setup() {
  Serial.begin(9600); // Default connection rate for my BT m

  // Setup motors
  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  motor_stop(); //initially motors are off
}

void loop() {
  //forward
  drive_forward();
  //Run for 5 seconds
  delay(5000);
  motor_stop();
  //Delay for 2 seconds
  delay(2000);
  //backward
  drive_backward();
  //Run for 5 seconds
  delay(5000);
  motor_stop();
  //Delay for 2 seconds
  delay(2000);
  //turn left
  turn_left();
  //Run for 5 seconds
  delay(5000);
  motor_stop();
  //Delay for 2 seconds
  delay(2000);
  //turn right
  turn_right();
  //Run for 5 seconds
  delay(5000);
  motor_stop();
  //Delay for 2 seconds
  delay(2000);

}

//Motor Controls
void motor_stop() {
  Serial.print("Motor :  STOP\n");
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

void turn_right() { //right
  Serial.print("Motor :  RIGHT\n");
  analogWrite(motor_left[0], PWMSpeed);
  digitalWrite(motor_left[1], LOW);

  analogWrite(motor_right[0], PWMSpeed);
  digitalWrite(motor_right[1], LOW);

}

void turn_left() { //left
  Serial.print("Motor :  LEFT\n");
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], PWMSpeed);

  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], PWMSpeed);

}

void drive_forward() { //forward
  Serial.print("Motor :  FORWARD\n");
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

void drive_backward() { //backward
  Serial.print("Motor :  BACK\n");
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

