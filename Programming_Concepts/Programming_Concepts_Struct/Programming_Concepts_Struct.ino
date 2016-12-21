//Structs

struct joystick_reading {
  int x_position; 
  int y_position; 
  boolean isButtonPressed;
};

joystick_reading currentReading;
int reading;

void setup() {

currentReading.x_position = 125;

currentReading.y_position = 225;

currentReading.isButtonPressed = false;


}

void loop() {
  // put your main code here, to run repeatedly:

}


