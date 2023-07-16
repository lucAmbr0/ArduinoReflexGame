// Arduino Reflex Game
// https://github.com/lucAmbr0/
// Created by @luca.ambroo_ [instagram]
// 01/15/2023
// Working on New Version on 07/16/2023

// Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
// Declaring the pins where you should connect your LCD


// Define pins
#define LED_A 4 // Left LED for Player A
#define LED_B 5 // Right LED for Player B
#define BUTTON_A 2 // Left Button for Player A
#define BUTTON_B 3 // Right Button for Player B
#define BUZZER 13

// Variables
int A_READY;
int B_READY;
int MODE;
int i;
int i2;
int delay1;
int A_PTS;
int B_PTS;
int ROUNDWIN;
// Some variables we'll use later


void setup() {
  Serial.begin(9600); // starts the serial monitor
  Serial.println("");
  Serial.println("Reflex Game");
  Serial.println("code by @luca.ambroo_"); // credits, please don't remove
  lcd.begin(16, 2); // configures the LCD display
  pinMode(LED_A, OUTPUT); // configuring pinModes
  pinMode(LED_B, OUTPUT);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  lcd.print("Reflex Game"); // Project Title
  lcd.setCursor(0, 1);
  delay(100);
  lcd.print("by luca.ambroo_"); // credits, please don't remove
  delay(1000);
  lcd.clear();
  delay(500);
  
  lcd.setCursor(0, 0); // A fast tutorial to explain the two main buttons to play
  Serial.println("Buttons tutorial displayed on LCD.");
  lcd.print("A  NAVIGATION  B");
  lcd.setCursor(0,1);
  lcd.print("A <  BUTTON  > B");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);

  MODE: // Player selects mode he wants to play to
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  MODE = 0;
  lcd.clear();
  Serial.println("Waiting for user to choose a game mode.");
  Serial.println("A: Light trigger");
  Serial.println("B: Sound trigger");
  lcd.print(">> SELECT MODE:");
  lcd.setCursor(0,1);
  lcd.print("A=LIGHT  B=SOUND");
  CHOOSEMODE:
  if (digitalRead(BUTTON_A) == LOW) {
    MODE = 1;
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("SELECTED LIGHT  ");
    Serial.println("User selected light mode");
    digitalWrite(LED_A, HIGH);
    delay(150);
    digitalWrite(LED_A, LOW);
    delay(300);
    goto LOBBY1; // go to lobby after decided game mode
  }
  else if (digitalRead(BUTTON_B) == LOW) {
    MODE = 2;
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("SELECTED SOUND  ");
    Serial.println("User selected sound mode");
    digitalWrite(LED_B, HIGH);
    delay(150);
    digitalWrite(LED_B, LOW);
    delay(300);
    goto LOBBY1; // go to lobby after decided game mode
  }
  else goto CHOOSEMODE; // repeat until a choice is made

  LOBBY1: // both player must click to mark as ready to play
  lcd.clear();
  delay(500);
  Serial.println("Lobby. Waiting for players");
  lcd.print("Player A WAITING");
  lcd.setCursor(0,1);
  lcd.print("Player B WAITING");
  LOBBY2:
  if (digitalRead(BUTTON_A) == LOW) {
    goto AREADY; }
  else if (digitalRead(BUTTON_B) == LOW) {
    goto BREADY; }
  
  if (A_READY >= 1) {
    if (B_READY >= 1) {
      delay(450);
      A_READY = 0;
      B_READY = 0;
      Serial.println("Both players are Ready");
      goto STARTGAME; // when they're both ready, start the game
    }
    }
  goto LOBBY2;

  AREADY:
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Player A READY");
  Serial.println("Player A is Ready");
  A_READY++;
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED_A, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  goto LOBBY2;

  BREADY:
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Player B READY");
  Serial.println("Player B is Ready");
  B_READY++;
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED_B, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  goto LOBBY2;

  STARTGAME: // simple loading animation
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  Serial.println("Starting the game");
  lcd.print("GAME IS STARTING");
  lcd.setCursor(0,1);
  for (i=0; i<=15; i++) {
    Serial.print(">");
    lcd.print(">");
    delay(150); }
  lcd.clear();
  Serial.println("");
  delay(500);
  if (MODE == 1) {
    goto LIGHT;
  }
  else if (MODE == 2) {
    goto SOUND;
  }
  else { lcd.print("fatal error."); }

  LIGHT: // here if you play with light trigger
  lcd.clear();
  lcd.print(" CLICK WHEN THE ");
  lcd.setCursor(0,1);
  lcd.print("  LEDS TURN ON  ");
  Serial.println("Displaying game instructions");
  delay(3000);
  lcd.clear();
  delay(200);
  lcd.print("  GET READY...  ");
  Serial.println("'Get Ready' displayed on LCD");
  delay(1200);
  lcd.clear();
  // false start will result in a penalty of -1 pt
  for (delay1=random(1000, 9500); delay1>=0; delay1--) {
    if (digitalRead(BUTTON_A) == LOW) {
      Serial.println("Player A has made a false start. Penalty applied.");
      lcd.print(">>FALSE  START<<");
      lcd.setCursor(0,1);
      lcd.print("PLAYER [A] -1 PT");
      A_PTS--;
      for (i2=0; i2<=3; i2++) {
        digitalWrite(LED_A, HIGH);
        digitalWrite(BUZZER, HIGH);
        delay(150);
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_A, LOW);
        delay(150); }
      delay(2000);
      goto SCORE;
      }
    else if (digitalRead(BUTTON_B) == LOW) {
      Serial.println("Player B has made a false start. Penalty applied.");
      lcd.print(">>FALSE  START<<");
      lcd.setCursor(0,1);
      lcd.print("PLAYER [B] -1 PT");
      B_PTS--;
      for (i2=0; i2<=3; i2++) {
        digitalWrite(LED_B, HIGH);
        tone(13, 50, 150);
        delay(150);
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_B, LOW);
        delay(50); }
      delay(2000);
      goto SCORE;
    }
    delay(1);
  }
  Serial.println("LIGHT TRIGGERED.");
  Serial.println("Waiting for input from players");
  LIGHTTRIGGER:
  lcd.print("OOOOOOOOOOOOOOOO");
  lcd.setCursor(0,1);
  lcd.print("OOOOOOOOOOOOOOOO");
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  // assigns the victory to the first that clicks the button
  if (digitalRead(BUTTON_A) == LOW) {
    A_PTS++;
    ROUNDWIN = 1;
    Serial.println("Player A has clicked the button");
    goto CONTINUE;
  }
  else if (digitalRead(BUTTON_B) == LOW) {
    B_PTS++;
    ROUNDWIN = 2;
    Serial.println("Player B has clicked the button");
    goto CONTINUE;
  }
  else goto LIGHTTRIGGER;

  SOUND: // here if you play with sound trigger
  lcd.clear();
  lcd.print(" CLICK WHEN THE ");
  lcd.setCursor(0,1);
  lcd.print("  BUZZER START  ");
  Serial.println("Displaying game instructions");
  delay(3000);
  lcd.clear();
  delay(200);
  lcd.print("  GET READY...  ");
  Serial.println("'Get Ready' displayed on LCD");
  delay(1200);
  lcd.clear();
  // false start will result in a penalty of -1 pt
  for (delay1=random(1000, 9500); delay1>=0; delay1--) {
    if (digitalRead(BUTTON_A) == LOW) {
      Serial.println("Player A has made a false start. Penalty applied.");
      lcd.print(">>FALSE  START<<");
      lcd.setCursor(0,1);
      lcd.print("PLAYER [A] -1 PT");
      A_PTS--;
      for (i2=0; i2<=3; i2++) {
        digitalWrite(LED_A, HIGH);
        digitalWrite(BUZZER, HIGH);
        delay(150);
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_A, LOW);
        delay(150); }
      delay(2000);
      goto SCORE;
      }
    else if (digitalRead(BUTTON_B) == LOW) {
      Serial.println("Player B has made a false start. Penalty applied.");
      lcd.print(">>FALSE  START<<");
      lcd.setCursor(0,1);
      lcd.print("PLAYER [B] -1 PT");
      B_PTS--;
      for (i2=0; i2<=3; i2++) {
        digitalWrite(LED_B, HIGH);
        digitalWrite(BUZZER, HIGH);
        delay(150);
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_B, LOW);
        delay(50); }
      delay(2000);
      goto SCORE;
    }
    delay(1);
  }
  Serial.println("LIGHT TRIGGERED.");
  Serial.println("Waiting for input from players");
  SOUNDTRIGGER:
  lcd.print("OOOOOOOOOOOOOOOO");
  lcd.setCursor(0,1);
  lcd.print("OOOOOOOOOOOOOOOO");
  digitalWrite(BUZZER, HIGH);
  // assigns the victory to the first that clicks the button
  if (digitalRead(BUTTON_A) == LOW) {
    A_PTS++;
    ROUNDWIN = 1;
    Serial.println("Player A has clicked the button");
    goto CONTINUE;
  }
  else if (digitalRead(BUTTON_B) == LOW) {
    B_PTS++;
    ROUNDWIN = 2;
    Serial.println("Player B has clicked the button");
    goto CONTINUE;
  }
  else goto SOUNDTRIGGER;

  CONTINUE:
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(BUZZER, HIGH);
  lcd.clear();
  delay(150);
  digitalWrite(BUZZER, LOW);
  delay(1500);
  lcd.print(" ROUND FINISHED ");
  Serial.println("The round has finished.");
  lcd.setCursor(0,1);
  delay(200);
  lcd.print("The winner is...");
  // suspense before revealing the winner XD
  delay(800);
  lcd.clear();
  if (ROUNDWIN == 1) {
    digitalWrite(BUZZER, HIGH);
    lcd.print(">>> PLAYER A <<<");
    lcd.setCursor(0,1);
    lcd.print("WON THIS ROUND!!");
    Serial.println("Player A has won this round");
    delay(150);
    digitalWrite(BUZZER, LOW);
    i = 0;
    for (i=0; i<=5; i++) {
      digitalWrite(LED_A, HIGH);
      delay(250);
      digitalWrite(LED_A, LOW);
      delay(100); }
  }
  else if (ROUNDWIN == 2) {
    digitalWrite(BUZZER, HIGH);
    lcd.print(">>> PLAYER B <<<");
    lcd.setCursor(0,1);
    lcd.print("WON THIS ROUND!!");
    Serial.println("Player B has won this round");
    delay(150);
    digitalWrite(BUZZER, LOW);
    i = 0;
    for (i=0; i<=5; i++) {
      digitalWrite(LED_B, HIGH);
      delay(250);
      digitalWrite(LED_B, LOW);
      delay(100); }
  }
  delay(1000);
  lcd.clear();
  goto SCORE;

  SCORE: // displays the total score of both players
  lcd.clear();
  Serial.println("Displaying the Total Score");
  Serial.print("Player A has ");
  Serial.print(A_PTS);
  Serial.println(" points");
  Serial.print("Player B has ");
  Serial.print(B_PTS);
  Serial.println(" points");
  lcd.print("  TOTAL SCORE:  ");
  lcd.setCursor(0,1);
  lcd.print("A: ");
  lcd.print(A_PTS);
  lcd.print("      B: ");
  lcd.print(B_PTS);
  delay(3000);
  lcd.clear();
  delay(250);
  // shows which player has more points
  if (A_PTS > B_PTS) {
  lcd.print(">> PLAYER [A] <<");
  lcd.setCursor(0,1);
  lcd.print(">> IS WINNING <<");
  Serial.println("Player A is winning the game");
  i = 0;
  for (i=0; i<=5; i++) {
    digitalWrite(LED_A, HIGH);
    delay(250);
    digitalWrite(LED_A, LOW);
    delay(100); }
  }
  else if (B_PTS > A_PTS) {
  lcd.print(">> PLAYER [B] <<");
  lcd.setCursor(0,1);
  lcd.print(">> IS WINNING <<");
  Serial.println("Player B is winning the game");
  i = 0;
  for (i=0; i<=5; i++) {
    digitalWrite(LED_B, HIGH);
    delay(250);
    digitalWrite(LED_B, LOW);
    delay(100); }
  }
  else { lcd.print("      DRAW      ");
  Serial.println("The game is tied"); }
  delay(1000);
  lcd.clear();
  // select a key to continue
  Serial.println("Waiting for user to make a choice");
  Serial.println("A: Next Round");
  Serial.println("B: Change Mode");
  lcd.print("A: NEXT ROUND");
  lcd.setCursor(0,1);
  lcd.print("B: CHANGE MODE");
  WAITINGSCREEN:
  if (digitalRead(BUTTON_A) == LOW) {
    lcd.clear();
    digitalWrite(LED_A, HIGH);
    delay(200);
    digitalWrite(LED_A, LOW);
    lcd.print(">> NEXT ROUND");
    Serial.println("User clicked A: Loading Next Round");
    lcd.setCursor(0,1);
    for (i=0; i<=15; i++) {
      lcd.print(">");
      delay(80); }
    goto LOBBY1; // starts a new round in the same mode
  }
  else if (digitalRead(BUTTON_B) == LOW) {
    lcd.clear();
    digitalWrite(LED_B, HIGH);
    delay(200);
    digitalWrite(LED_B, LOW);
    lcd.print(">> CHANGE MODE");
    Serial.println("User clicked B: Loading Mode Selector");
    lcd.setCursor(0,1);
    for (i=0; i<=15; i++) {
      lcd.print(">");
      delay(150); }
    goto MODE; // makes user change game mode
  }
  else goto WAITINGSCREEN; // waits for the user to make a choice
}

//
//              _..._
//            .'     '.      _
//           /    .-""-\   _/ \
//         .-|   /:.   |  |   |
//         |  \  |:.   /.-'-./
//         | .-'-;:__.'    =/
//         .'=  *=|     _.='
//        /   _.  |    ;
//       ;-.-'|    \   |     @luca.ambroo__
//      /   | \    _\  _\
//      \__/'._;.  ==' ==\
//              \    \   |
//              /    /   /
//             /-._/-._/
//             \   `\  \
//              `-._/._/
//