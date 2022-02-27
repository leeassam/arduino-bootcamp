/*
  Retreive Weather From Weather Underground

  This sketch connects to the Weather Underground API to make a request
  using an Arduino Wifi shield. The result is displayed on an LCD display.
  
  by: Lee Assam

*/

#include <WiFi.h>
#include <LiquidCrystal.h>


char ssid[] = "Your network name";      //  your network SSID (name)
char pass[] = "Your network password";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "api.wunderground.com";

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 30L * 1000L; // delay between updates, in milliseconds


String responseString = "";            // Response string from server for .JSON page
int APItemp;                           // Integer temperature from .JSON page
boolean tempFound = false;             // Indicator for temperature found
boolean tempStringFound = false;       // Indicator for weather temperature found
boolean weatherFound = false;          // Indicator for weather found
boolean humidityFound = false;         // Indicator for humidity found

char weather[30];
char weatherString[30];
char humidity[4];

//API information
String apiKey = "Your api key";
//US
String state = "IL";
String city = "Bloomington";
String weatherLocation = String(state + "/" + city);

//International
//String country = "Name of your Country";
//String city = "City in your Country";
//String weatherLocation = String(country +  "/" + city);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 8, 9);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Retrieving");
  lcd.setCursor(0, 1);
  lcd.print("Weather...");

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    //status = WiFi.begin(ssid, pass);
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  boolean startCapture = false;          // Boolean for indicating JSON capture
  String response = "";                  // Initialize the response string
  tempFound = false;                     // Indicator for temperature found
  tempStringFound = false;
  weatherFound = false;                  // Indicator for weather found
  humidityFound = false;

  while (client.available())
  {
    char inChar = client.read();
    if (inChar == '"')
      startCapture = true;
    else if (startCapture)
    {
      responseString += inChar;
      if (inChar == ',')
      {
        startCapture = false;
        checkData();
      }
    }
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

  displayWeather();

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    String urlRequest = String("GET /api/" + apiKey + "/conditions/q/" + weatherLocation + ".json HTTP/1.1");
    client.println(urlRequest);
    client.println("Host: api.wunderground.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



/*******************************************************************************************************************************
  void checkData()
********************
  Purpose: Upates the response values from a string containing the API response .JSON file
  Entry: int APItemp and char weather contain outdated values
  Exit: int APItemp - updated
        char[] weather - updated
*******************************************************************************************************************************/
void checkData()
{
  int i;                                                            // Variable for string length
  if (responseString.startsWith(F("temp_f")) & !tempFound)          // If this is the temp_f line and we havent found temperature
  {
    char temp2[3];                                                  // Allocate temporary temperature variable
    tempFound = true;                                               // We have found temperature, so update variable
    for (i = 7; i < responseString.length() - 1; ++i )              // For the length of the response string
    {
      if (responseString[i] == '.')                                 // If we found a '.' break the loop
        break;
      temp2[i - 7] = responseString[i];                             // Otherwise add the character to temperature
    }
    APItemp = atoi(temp2);                                          // Convert char to int and store in global
    Serial.print("Temperature: ");
    Serial.println(APItemp);
  }
  else if (responseString.startsWith(F("weather")) & !weatherFound) // If this is the weather line and we haven't found weather
  {
    memset(weather, 0, sizeof(weather));
    weatherFound = true;                                            // We have found weather, so update variable
    for (i = 8; i < responseString.length() - 1; ++i )              // For the length of the response string
      weather[i - 8] = responseString[i];                           // Append the character on the response string
    Serial.print("Weather: ");
    Serial.println(weather);
  }
  else if (responseString.startsWith(F("relative_humidity")) & !humidityFound) // If this is the humidity line and we haven't found humidity
  {
    memset(humidity, 0, sizeof(humidity));
    humidityFound = true;                                            // We have found weather, so update variable
    for (i = 18; i < responseString.length() - 1; ++i )              // For the length of the response string
      humidity[i - 18] = responseString[i];                          // Append the character on the response string
    Serial.print("Humidity: ");
    Serial.println(humidity);
  }
  else if (responseString.startsWith(F("temperature_string")) & !tempStringFound) // If this is the location line and we haven't found location
  {
    memset(weatherString, 0, sizeof(weatherString));
    tempStringFound = true;                                          // We have found weather, so update variable
    for (i = 19; i < responseString.length() - 1; ++i )              // For the length of the response string
      weatherString[i - 19] = responseString[i];                     // Append the character on the response string
    Serial.print("Weather String: ");
    Serial.println(weatherString);
  }
  responseString = "";                                              // Clear the response string
}

void displayWeather() {
  if (strlen(weatherString) != 0) {
    //Display weather description
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weather: ");
    lcd.setCursor(0, 1);
    lcd.print(weather);
    delay(3000);
    //Display temperature
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.setCursor(0, 1);
    lcd.print(weatherString);
    delay(3000);
    //Display humidity
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.setCursor(0, 1);
    lcd.print(humidity);
    delay(3000);
  }
}



