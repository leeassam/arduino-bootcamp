/*
  Arduino Bootcamp

  - Joystick LED Matrix Game

  This project demonstrates how a joytstick can be used in conjunction with an 8 x 8 LED Matrix to create a game.
  The object of the game is to capture the falling ball on platform that you control with the joystick

  by: Lee Assam

*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <StopWatch.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const int pinRandom = A0;

const int wait = 300; // In milliseconds
const int length = 8;

int x[length], y[length];
int ptr, nextPtr;

//Joystick
int matrix_x, matrix_y;
int curr_matrix_x = 0;
int curr_matrix_y=0;
int curr_fall_x = 0;
int curr_fall_y = 0;
int vertical, horizontal, select;
const int VERT = 0; // analog
const int HORIZ = 1; // analog
const int SEL = A2; // digital

//Create stopwatch object
StopWatch SW_secs(StopWatch::SECONDS);
int timeToWin = 10; //seconds

void setup() {
  matrix.setIntensity(4); // Set brightness between 0 and 15

  // Reset all variables
  for ( ptr = 0; ptr < length; ptr++ ) {
    x[ptr] = numberOfHorizontalDisplays * 8 / 2;
    y[ptr] = numberOfVerticalDisplays * 8 / 2;
  }
  nextPtr = 0;

  randomSeed(analogRead(pinRandom)); // Initialize random generator

  //Joystick
  // make the SEL line an input
  pinMode(SEL, INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL, HIGH);
  // set up serial port for output
  Serial.begin(115200);
  startGame();
}

void loop() {
  playGame();
  if (SW_secs.elapsed() >=timeToWin) {
    winner();
  }
}

//Draws scrolling text on the LED Matrix
void drawScrollingText(String text) {
  if (text.length() > 0) {
    //Draw scrolling text
    int spacer = 1;                            // This will scroll the string
    int width = 5 + spacer;                    // The font width is 5 pixels
    for ( int i = 0 ; i < width * text.length() + width - 1 - spacer; i++ ) {

      matrix.fillScreen(0);

      int letter = i / width;
      int x = (matrix.width() - 1) - i % width;
      int y = (matrix.height() - 8) / 2; // center the text vertically

      while ( x + width - spacer >= 0 && letter >= 0 ) {
        if ( letter < text.length() ) {
          matrix.drawChar(x, y, text[letter], 1, 0, 1);
        }

        letter--;
        x -= width;
      }

      matrix.write(); // Send bitmap to display

      delay(100);
    }
  }
}

//Draws text on the LED Matrix
void drawText(String input) {
  //Draw Text
if (input.length() > 0 ) {
 for (int i = 0; i<input.length(); i++) // Loop through the contents of the string
 {
  matrix.fillScreen(0);                     // Clear the display before showing the next char
  matrix.drawChar(0,0,input[i],1,0,1);  // Draw a char to the buffer
  matrix.write();                           // Draw the buffer to the display
  delay(1000);  
  matrix.fillScreen(0);  
  matrix.write();  
  delay(20);
 }
}
}



void playGame () {
  int y = random(0, 8);
  //matrix.write();
  for (int i = 0; i < 8; i++) {
    matrix.drawPixel(i, y, HIGH);
    curr_fall_x = i;
    curr_fall_y = y;
    setJoystickPosition();
    matrix.write();
    delay(wait);
    matrix.drawPixel(i, y, LOW);
    matrix.write();    
    if (collisionOccurred()) {
      Serial.println("Hit");
      return;
    }
    //check if falling pixel made it all the way off the screen
    if (i==7) {
      gameOver();
    }
  }
}

//Draws the position of the platform on the matrix which you control via the joystick
void setJoystickPosition() {
    // Read all values from the joystick
    vertical = analogRead(VERT); // will be 0-1023
    horizontal = analogRead(HORIZ); // will be 0-1023
    select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed

    matrix_y = map(vertical, 5, 1018, 7, 0); // Maps values in the range
                                         // 0 to 1023 to the range
                                         // 7 to 0
    matrix_x = map(horizontal, 1018, 5, 0, 7);

    //Remove old joystick position
    matrix.drawPixel(curr_matrix_x, curr_matrix_y, LOW);
    //Set new joystick position
    matrix.drawPixel(matrix_x, matrix_y, HIGH);

    //Remove previously lit pixels to the left and right of the old joystick position
    matrix.drawPixel(curr_matrix_x, curr_matrix_y-1, LOW);
    matrix.drawPixel(curr_matrix_x, curr_matrix_y+1, LOW);
    //Add new additional pixels to the left and right
    matrix.drawPixel(matrix_x, matrix_y+1, HIGH);
    matrix.drawPixel(matrix_x, matrix_y-1, HIGH);

    //Keep track of global position
    curr_matrix_x = matrix_x;
    curr_matrix_y = matrix_y;
}

void startGame() {
  SW_secs.reset();
  SW_secs.start();
}

//Display winning message
void winner() {
 // drawScrollingText("Win");
 Serial.println("WIN");
  drawText("Win");
  
  startGame(); 
}

//Display game over message
void gameOver() {
  //drawScrollingText("Game Over");
   Serial.println("LOOSE");
  drawText("Loose");
  startGame();
}

//Determine if a collision has occured between falling ball and platform
boolean collisionOccurred() {
  //if falling pixel is above or on the current jostick line, a collision has occurred
   return ( ((curr_matrix_x == curr_fall_x) || (curr_matrix_x == curr_fall_x+1)) && ((curr_matrix_y == curr_fall_y) 
            || (curr_matrix_y+1 == curr_fall_y) ||
            (curr_matrix_y-1 == curr_fall_y) )) ;            
}

