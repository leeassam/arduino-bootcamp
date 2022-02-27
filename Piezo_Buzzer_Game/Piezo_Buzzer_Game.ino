/*
Arduino Bootcamp

- Piezo Buzzer Sound Recall Game

This project demonstrates a game with piezo buzzers. 
The objective is to play back the sounds that are heard in the exact order that they are played.

by: Lee Assam

*/
#include <Bounce2.h>

//The +ve buzzer pin is connected to pin 9 of the Arduino
//Defining the buzzers
#define buzzer1 8
#define buzzer2 9
#define buzzer3 10
// Defining the buttons
#define button1 5
#define button2 6
#define button3 7

// Instantiate Bounce objects
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 

//Change this variable to increase number of notes to play
int noteSequence[4];
int numNotes =  sizeof(noteSequence)/sizeof(int);
int currentNote = 0;
boolean challengePlayed = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  //Defining internal pullups
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  
  // After setting up the buttons, setup the Bounce instances :
  debouncer1.attach(button1);
  debouncer1.interval(5); // interval in ms  
  debouncer2.attach(button2);
  debouncer2.interval(5); // interval in ms  
  debouncer3.attach(button3);
  debouncer3.interval(5); // interval in ms   

  //get first sequence of notes
  //generating a random number
  randomSeed(analogRead(0));
  generateRandomPlaySequence();
}

// the loop function runs over and over again forever
void loop() {

if (!challengePlayed) {
    challengePlayed = true;
    currentNote = 0;    
    playSequence(noteSequence);
}

  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();

  // Get the updated values :
  int value1 = debouncer1.read();
  int value2 = debouncer2.read();  
  int value3 = debouncer3.read();
  
   if ( debouncer1.fell()  ) {
    playNote(1);
    verifyNotePlayedIsCorrect(1);
  }
  
   if ( debouncer2.fell()  ) {
    playNote(2);   
    verifyNotePlayedIsCorrect(2);
  }

   if ( debouncer3.fell()  ) {
    playNote(3);
    verifyNotePlayedIsCorrect(3);
  }
}

void playSequence(int notes[]) {
 for (int i=0; i< numNotes; i++) {
  playNote(notes[i]);
 }
}

void verifyNotePlayedIsCorrect(int note) {
 if (currentNote < numNotes) {
  if (noteSequence[currentNote] == note) {
    currentNote++;
    if (currentNote == numNotes) {
     winner();      
    }
  } else {
    looser();
  }
 }
  
}

void playNote(int note) {
  switch (note) {
    case 1:
    tone(buzzer1, 2000);
    delay(750);
    noTone(buzzer1);
    delay (500);
    break;
    case 2:
    tone(buzzer2, 4000);
    delay(750);
    noTone(buzzer2);
    delay (500);    
    break;
    case 3:
    tone(buzzer3, 6000);
    delay(750);
    noTone(buzzer3);
    delay (500);    
    break;        
    default:
    break;
  }
  
}

void winner() {
  currentNote = 0;
  challengePlayed = false;  
  generateRandomPlaySequence();
  for (int i =0; i <3; i++) {
  tone(buzzer3, 2000);
  delay(250);
  noTone(buzzer3);
  delay(250);
  }
  delay(2000);
}

void looser() {
  currentNote = 0;
  challengePlayed = false;
  tone(buzzer1, 200);
  delay(1000);
  noTone(buzzer1);
  delay(2000);
}

void generateRandomPlaySequence() {
 for (int i = 0; i < numNotes; i ++ ) {
    int num = random(1, 4);
     Serial.println(num);
    noteSequence[i] = num;
 }

}

