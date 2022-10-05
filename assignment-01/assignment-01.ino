#include <avr/sleep.h>
#include <math.h>
//#include "TimerOne.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4

//arduino environment
int ledPins[NLED];
int redLedPin;
int buttonPins[NLED];
int potentiometerPin;

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

void updateStates(){
  for(int i = 0; i < NLED; i++){
      uint8_t value = ledPins[i] == 0 ? LOW : HIGH;
      digitalWrite(ledPins[i], value);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (gameState) {
    case 1:  //initial state
      noInterrupts();

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

      break;
    case 2:  //in game
             // code block
             //check sequence from button
             //ligh led up
      break;
    case 3:
    //ligh up led for game start
    default:  //sleepmode
      interrupts();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      // create new sequence
      //
  }
}
void newSequence() {
  for (int i = 0; i < NLED; i++) {
    sequence[i] = rand() * NLED;
  }
}