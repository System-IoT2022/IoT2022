#include <avr/sleep.h>
#include <math.h>
//#include "TimerOne.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4
#define SLEEPMODE 1000
#define T1 10

//arduino environment
int ledPins[NLED];
int redLedPin;
int buttonPins[NLED];
int potentiometerPin;
unsigned long time_now;


//game settings
short int gameState;
int score = 0;
int penalty = 0;

//game logics
int redLed;
int buttonStates[NLED];
int ledStates[NLED];
int sequence[NLED];
int potentiometer;

void gameStart(){
  for(int i = 0; i < NLED; i++){
    ledStates[i] = 0;
    sequence[i] = 0;
  }
  score = 0;
  penalty = 0;
  gameState = 2;
  time_now = millis();
}



void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wake, RISING);
  for (int i = 0; i < NLED; i++) {
    ledPins[i] = 10 + i;
    buttonPins[i] = 5 + i;
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
  redLedPin = 9;
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);
  //Timer1.initialize(1000000); 
}
void wake() {
  gameState = 1;
  sleep_disable();
}

void polling(){
  //read inputs including: buttons, potentionmeter
    for(int i = 0; i < NLED; i++){
      buttonStates[i] = digitalRead(buttonPins[i]);
    }
    //potentiometer = digitalRead(potentiometerPin);
}

void updateLedStates(){
  for(int i = 0; i < NLED; i++){
      uint8_t value = ledPins[i] == 0 ? LOW : HIGH;
      digitalWrite(ledPins[i], value);
  }
}

void redLedFading(){

}

void checkPenalty(){

      if (penalty == 0) {
        //check start game
      }
      {
        if (penalty == 3) {
          //game over
          penalty = 0;
        } else {

          newSequence();  // new sequence list
          gameState = 3;
        }
      }
}
/*1: restarted game
  2: waiting user
  3: game starts
  sleeping mode*/
void loop() {
  // put your main code here, to run repeatedly:
  polling();
  switch (gameState) {
    case 1:  //initial state
      noInterrupts();
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      gameState = 2;
      break;
    case 2:  
     //wait for 10 seconds
      if(millis() < time_now + T1){
        redLedFading();
        if(buttonStates[0] == HIGH){
          gameState = 3;
        }
        
      }else{ /*after 10 secodns, go deep sleep mode.*/
        gameState = SLEEPMODE;
      }
      break;
    case 3:
    //ligh up led for game start
    default:  //sleepmode
      interrupts();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      /*during deep sleeping mode*/
      
      /** The program will continue from here. **/
      Serial.println("WAKE UP");
      /* First thing to do is disable sleep. */
      wake();
  }
}
void newSequence() {
  for (int i = 0; i < NLED; i++) {
    sequence[i] = rand() * NLED;
  }
}