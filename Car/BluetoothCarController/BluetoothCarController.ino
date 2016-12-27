/*
  Arduino Bootcamp

  - Remote Controlled Car - Controlling via an Android App - Part 5

  This project demonstrates how a car with two motors can be controlled via Bluetooth using a smart phone app.

  created 10/30/2016
  modified 10/30/2016
  by: Lee Assam

*/

// —————————————————————————  Motors
//Pins must be PWM to control motor speed on turns
int motor_left[] = {3, 5};
int motor_right[] = {9, 6};

int command = 0;
//PWM - To slow down left and right turns
int PWMSpeed = 125;

void setup() {
  //Configure internal pullup on the RX pin
  pinMode(0, INPUT_PULLUP);  
  Serial.begin(9600); // Default connection rate for bluetooth module
  
  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  motor_stop(); //initially motors are off
}

void loop() {
    
  // if there's data available, read a packet
    //if some data is sent, read it and save it in the state variable
    if(Serial.available() > 0){
      command = Serial.read();
    //Process command
    if(command == '1'){
      drive_forward();
    } else if(command == '2'){
      drive_backward();
    } else if(command == '3') {
      turn_right(); 
    } else if(command == '4') {
      turn_left();
    } else if(command == '0') {
      motor_stop();        
    } else {
      motor_stop();
    }
   }
}

//Motor Controls
void motor_stop(){
  Serial.print("Motor :  STOP\n");  
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

void turn_right(){ //right
  //Slow down speed by using PWM
  Serial.print("Motor :  RIGHT\n");
  analogWrite(motor_left[0], PWMSpeed);
  digitalWrite(motor_left[1], LOW);

  analogWrite(motor_right[0], PWMSpeed);
  digitalWrite(motor_right[1], LOW);  
  
}

void turn_left(){ //left
  //Slow down speed by using PWM
  Serial.print("Motor :  LEFT\n"); 
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], PWMSpeed);

  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], PWMSpeed);  
  
}

void drive_forward(){ //forward
  Serial.print("Motor :  FORWARD\n");
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

void drive_backward(){ //backward
  Serial.print("Motor :  BACK\n");
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

