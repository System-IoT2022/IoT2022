#include <avr/sleep.h>
#include <math.h>
//#include "TimerOne.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4
#define SLEEPMODE 1000
#define WAITING_TIME 10000
#define T1 3000
#define T2 3000
#define T3 5000
#define GAME_REWARD 10

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

/*initializing for game onset*/
void gameStart(){
  for(int i = 0; i < NLED; i++){
    sequence[i] = 0;
  }
  turnOffLeds();
  score = 0;
  penalty = 0;
  gameState = 2;
}
/*turn off all lights*/
void turnOffLeds(){
  for(int i = 0; i < NLED; i++){
    ledStates[i] = 0;
    redLed = 0;
  }
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
/*wake up the system during interrupts*/
void wake() {
  gameState = 1;
  sleep_disable();
}

  /*read inputs including: buttons, potentionmeter*/
void polling(){
    for(int i = 0; i < NLED; i++){
      buttonStates[i] = digitalRead(buttonPins[i]);
    }
    //potentiometer = digitalRead(potentiometerPin);
}
/*update the light based on the states*/
void updateLedStates(){
  for(int i = 0; i < NLED; i++){
      uint8_t value = ledPins[i] == 0 ? LOW : HIGH;
      digitalWrite(ledPins[i], value);
  }
}
/*sets the light states*/
void turnOnLights(int sequence[NLED]){

}
/*a new sequence used for turning on lights*/
void createNewSequence(int sequence[NLED]){

}
/* the functions does analog write from 0 to 255 */
void redLedFading(){

}
/*check whether the user was able to recreate the lighting sequence*/
bool wereUserInputsCorrect(){

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

//here i should apply penalty to user when he touches any buttons
void applayPenaltyToUserForAnyInputs(){

}
void loop() {
  polling();
  switch (gameState) {
    case 1:  //initial state
      noInterrupts();
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      time_now = millis();
      gameState = 2;
      break;
    case 2:  //wait interaction from the user for 10 seconds
      if(millis() < time_now + WAITING_TIME){
        redLedFading();
        if(buttonStates[0] == HIGH){
          gameState = 3;
        }
        
      }else{ /*after 10 secodns, go deep sleep mode.*/
        gameState = SLEEPMODE;
      }
      break;
    case 3: //Game starts!
      
      gameStart();
      Serial.println("GO");
      gameState = 4;
      break;
    case 4: //during game{showing patterns}
      //wait a bit for T1 milliseconds
      turnOffLeds();
      delay(random(T1));
      //show tricks  for T2 milliseconds
      createNewSequence(sequence);
      turnOnLights(sequence);
      delay(random(T2)); 
      applayPenaltyToUserForAnyInputs();
      time_now = millis();
      gameState = 5;
      break;
    case 5: //during game{user inputs}
      //input time for T3 milliseconds
      turnOffLeds();
      if(millis < time_now + T3){
        // do nothing, waiting user to finish inputs
      }else{
        //exsamination of the inputs
        if(wereUserInputsCorrect()){
          score += GAME_REWARD;
          Serial.println(String("New point! Score: ") + score);
        }else{
          penalty += 1;
          Serial.println("Penalty!");
          digitalWrite(redLedPin, HIGH);
          delay(1000);
          if(Penalty == 3){
            Serial.println(String("Game Over. Final Score: ") + score);
            gameState = 1;
          }
        }
      }

      break;
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