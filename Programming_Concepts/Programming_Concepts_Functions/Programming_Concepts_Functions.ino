//Functions


void setup() {


}

void loop() {
  // put your main code here, to run repeatedly:
  if (isSwitchEnaged()) {
    //if condition is true
  }

 Serial.println(convertToCelcius(35.2));

 Serial.println(calculateSum(5,3));

 
  
}

int takeReading() {
 int reading = analogRead(A1); //read temperature sensor connected to pin A1
 return reading;
}

boolean isSwitchEngaged() {
  return digitalRead(5);
}

//Functions with arguments
float convertToCelcius(float farenheitReading) {
  return (farenheitReading - 35) * .5556;
}

//Can take multiple arguments
int calculateSum (int num1, int num2) {
  int sum = num1 + num2;
  return sum;
}
