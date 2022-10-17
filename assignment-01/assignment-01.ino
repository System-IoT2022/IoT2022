/*This project is co-implemented by Diego Giusepetti,  Giuseppe Pintus and zhaohui Song authored for the submission. */
#include <avr/sleep.h>
#include <avr/power.h>
#include <math.h>
#include "ButtonLeds.h"
#include "TimerDelay.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4

#define WAITING_TIME 10
#define T1 2
#define T2 3
#define T3 6
#define GAME_REWARD 10
#define REDLEDPIN 9

#define WELCOME 1
#define USER_INPUT 2
#define GAME_START 3
#define DURING_GAME 4
#define SHOW_SEQUENCE 5
#define END_GAME 6
#define SLEEPMODE 7
#define WAKING_STATE 8
#define PENALTY 9
#define AFTER_PENALTY 10
//arduino environment
int ledPins[NLED] = { 5, 6, 7, 8 };
int redLedPin;
int buttonPins[NLED] = { 10, 11, 12, 13 };
int potentiometerPin;
unsigned long time_now;
unsigned long lastPress = 0;
ButtonLeds* buttonLeds;
TimerDelay* twait;

//game settings
int gameState;
int score = 0;
int penalty = 0;
int fadeAmount = 1;
int currIntensity = 0;

//game logics
int redLed;
int buttonStates[NLED];
int ledStates[NLED];
int sequence[NLED];
int* potentiometer;
int speedUp;
float factor;
void wakeUp() {
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wakeUp, RISING);
  redLedPin = REDLEDPIN;
  pinMode(redLedPin, OUTPUT);
  gameState = WELCOME;
  buttonLeds = new ButtonLeds(buttonPins, ledPins, NLED);
  buttonLeds->init(INPUT_PULLUP);
  randomSeed(analogRead(0));
  twait = new TimerDelay();
  potentiometer = 1;
  factor = 1;
  speedUp = 1;
}

void loop() {
  //Serial.println(currIntensity);
  switch (gameState) {
    case WELCOME:
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      speedUp = setDifficult(analogRead(potentiometerPin));
      Serial.println("Difficulty select at :" + String(speedUp) + " [1x-4x]");
      gameState = USER_INPUT;
      configureDistinct();
      twait->resetTimer();
      break;
    case USER_INPUT:                     //wait interaction from the user for 10 seconds
      if (twait->delay2(WAITING_TIME)) { /*after 10 secodns, go deep sleep mode.*/
        analogWrite(REDLEDPIN, LOW);
        gameState = SLEEPMODE;
        twait->resetTimer();
      } else {
        ledFading(REDLEDPIN, &currIntensity, &fadeAmount);
        if (digitalRead(buttonPins[0]) == LOW) {
          gameState = GAME_START;
        }
      }
      break;
    case GAME_START:  //Game starts!
      gameStart();
      Serial.println("GO!");
      twait->resetTimer();
      break;
    case DURING_GAME:  //during game{showing patterns}

      if (twait->delay2(T1)) {
        do {
          createNewSequence(sequence, 2);
        } while (ledOn(sequence) == 0);  //check if at least one led is on in the sequence
        turnOnLights(sequence);
        gameState = SHOW_SEQUENCE;
        twait->resetTimer();
      }
      break;
    case SHOW_SEQUENCE:
      if (twait->delay2(T2 / (speedUp * factor))) {
        //time_now = millis();//no more usefull???
        turnOffLeds();
        gameState = END_GAME;
        twait->resetTimer();
      } else {
        //CHECK INPUT
        if (buttonLeds->polling(true)) {
          turnOffLeds();
          gameState = PENALTY;
          Serial.println("you got penalty by pressing during sequence!");
          digitalWrite(redLedPin, HIGH);
          twait->resetTimer();
        }
      }
      break;
    case END_GAME:  //game{user inputs}
      //input time for T3 milliseconds

      if (twait->delay2(T3 / (speedUp * factor))) {
        turnOffLeds();
        //exsamination of the inputs
        if (wereUserInputsCorrect()) {
          //Serial.println("new turn");
          score += GAME_REWARD * speedUp * speedUp * factor;
          Serial.println(String("New point! Score: ") + score);
          gameState = DURING_GAME;
          factor *= 1.04;

        } else {

          gameState = PENALTY;
          Serial.println("Penalty!");
          digitalWrite(redLedPin, HIGH);
        }
        resetInput();
        twait->resetTimer();
      } else {
        getUserMoves();
        buttonLeds->polling(true);
      }

      break;
    case PENALTY:

      if (twait->delay2(1)) {
        penalty++;
        gameState = DURING_GAME;
        if (penalty == 3) {
          Serial.println(String("Game Over. Final Score: ") + score);
          gameState = AFTER_PENALTY;
          twait->resetTimer();
        }
        turnOffLeds();
      }
      break;
      case AFTER_PENALTY:
      if (twait->delay2(10)) {
          gameState = WELCOME;
          penalty = 0;
      }
      break;
    case SLEEPMODE:
      Serial.println("Turning off the platform....");
      Serial.flush();
      interrupts();
      configureCommon();
      turnOffLeds();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      /*during deep sleeping mode*/

      sleep_disable();

      Serial.println(".... Waking up the platform.");

      delay(500);
      gameState = WELCOME;
      break;
    default:
      break;
  }
}



/*update the light based on the states*/
void updateLedStates() {
  for (int i = 0; i < NLED; i++) {
    uint8_t value = ledStates[i] == 0 ? LOW : HIGH;
    digitalWrite(ledPins[i], value);
  }
  digitalWrite(redLedPin, LOW);
}
/*sets the light states*/
void turnOnLights(int sequence[NLED]) {
  for (int i = 0; i < NLED; i++) {
    ledStates[i] = sequence[i];
  }
  updateLedStates();
}
/*a new sequence used for turning on lights*/
void createNewSequence(int sequence[NLED], int range) {
  for (int i = 0; i < NLED; i++) {
    sequence[i] = random(range);
  }
}
/*count number of leds*/
int ledOn(int sequence[NLED]) {
  int c = 0;
  for (int i = 0; i < NLED; i++) {
    if (sequence[i]) {
      c++;
    }
  }
  return c;
}
/* the functions does analog write from 0 to 255 */
void ledFading(const int LED_PIN, int* currIntensity, int* fadeAmount) {
  analogWrite(LED_PIN, *currIntensity);
  *currIntensity = *currIntensity + *fadeAmount;
  if (*currIntensity < 1 || *currIntensity > 150) {  //150 bcs too brigth
    *fadeAmount = -*fadeAmount;
  }
  delay(5);
}
bool resetInput() {
  for (int i = 0; i < NLED; i++) {
    buttonStates[i] = 0;
  }
}
/*check whether the user was able to recreate the lighting sequence*/
bool wereUserInputsCorrect() {
  /*Serial.println("user input:");
  for (int i = 0; i < NLED; i++) {

    Serial.print(buttonStates[i] + String(" "));
  }
  Serial.println("");

  Serial.println("sequenze generated");
  for (int i = 0; i < NLED; i++) {
    Serial.print(sequence[i] + String(" "));
  }
  Serial.println("");
  */
  for (int i = 0; i < NLED; i++) {
    if (sequence[i] != buttonStates[i]) {
      return false;
    }
  }
  return true;
}

void getUserMoves() {
  for (int i = 0; i < NLED; i++) {
    if (buttonStates[i] == 0) {
      buttonStates[i] = digitalRead(buttonPins[i]) == LOW ? 1 : 0;
    }
  }
  //Serial.println("");
}

void configureCommon() {  //any pressed button
  pinMode(WAKE_UP_PIN, INPUT_PULLUP);
  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
  }
}
void configureDistinct() {  // distinct button are recognized when pressed
  pinMode(WAKE_UP_PIN, OUTPUT);
  digitalWrite(WAKE_UP_PIN, HIGH);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

/*initializing for game onset*/
void gameStart() {
  for (int i = 0; i < NLED; i++) {
    sequence[i] = 0;
  }
  turnOffLeds();
  digitalWrite(redLedPin, LOW);
  score = 0;
  penalty = 0;
  factor = 1;
  gameState = DURING_GAME;
}
/*turn off all lights*/
void turnOffLeds() {
  for (int i = 0; i < NLED; i++) {
    ledStates[i] = 0;
    redLed = 0;
  }
  updateLedStates();
}

int setDifficult(int value) {
  value = ((value < 255 ? 255 : value) / 255);
  return value;
}
