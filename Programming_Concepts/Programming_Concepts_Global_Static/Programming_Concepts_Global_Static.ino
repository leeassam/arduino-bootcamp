//Local variables vs Global variables

//Global Variable
int motorSpeed;
float temperatureReading;
boolean completed; //global variable

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

int calculateSum(int num1, int num2) {
  int result; /*local variable*/
  result = num1 + num2;
  return result;
}

