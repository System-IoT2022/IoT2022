#include <avr/sleep.h>
#include <math.h>
#include "ButtonLeds.h"
//#include "TimerOne.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4

#define WAITING_TIME 10000
#define T1 3000
#define T2 3000
#define T3 10000
#define GAME_REWARD 10
#define REDLEDPIN 9

#define WELCOME 1
#define USER_INPUT 2
#define GAME_START 3
#define DURING_GAME 4
#define END_GAME 5
#define SLEEPMODE 6
#define WAKING_STATE 7
//arduino environment
int ledPins[NLED] = { 5, 6, 7, 8 };
int redLedPin;
int redIntensity;
int buttonPins[NLED] = { 10, 11, 12, 13 };
int potentiometerPin;
unsigned long time_now;
unsigned long lastPress = 0;
boolean interruptStatePressed;
ButtonLeds* buttonLeds;

//game settings
short int gameState;
int score = 0;
int penalty = 0;
int fadeAmount = 5;
int currIntensity = 0;

//game logics
int redLed;
int buttonStates[NLED];
int ledStates[NLED];
int sequence[NLED];
float potentiometer;


void wakeUp() {
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wakeUp, RISING);
  interruptStatePressed = false;
  redIntensity = 0;
  redLedPin = REDLEDPIN;
  pinMode(redLedPin, OUTPUT);
  gameState = WELCOME;
  buttonLeds = new ButtonLeds(buttonPins, ledPins, NLED);
  buttonLeds->init(INPUT_PULLUP);
  potentiometer=1;
  //Timer1.initialize(1000000);
}

void loop() {
  //polling();

  //updateLedStates();
  //Serial.println(gameState);
  switch (gameState) {
    case WELCOME:  //initial state
      //noInterrupts();
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      delay(1000);
      time_now = millis();
      gameState = USER_INPUT;
      configureDistinct();
      //turnOffLeds();
      break;
    case USER_INPUT:  //wait interaction from the user for 10 seconds
      if (millis() < time_now + WAITING_TIME*potentiometer) {
        //analogWrite(redLedPin, currIntensity);

        ledFading(REDLEDPIN, &currIntensity, &fadeAmount);

        noInterrupts();
        if (buttonLeds->polling(false)) {
          gameState = GAME_START;
        }
        interrupts();
        // Serial.println(millis());

      } else { /*after 10 secodns, go deep sleep mode.*/
        analogWrite(REDLEDPIN, LOW);
        gameState = SLEEPMODE;
      }
      break;
    case GAME_START:  //Game starts!
      //configureDistinct();
      gameStart();
      Serial.println("GO!");
      break;
    case DURING_GAME:  //during game{showing patterns}

      //show tricks  for T2 milliseconds
      createNewSequence(sequence, 2);
      if (ledOn(sequence) >= 1) {
        //wait a bit for T1 milliseconds
        delay(T1/potentiometer);
        //check if at least one led is on
        turnOnLights(sequence);
        delay(T2/potentiometer);
        //applayPenaltyToUserForAnyInputs();
        time_now = millis();
        gameState = END_GAME;
        turnOffLeds();
      }
      break;
    case END_GAME:  //game{user inputs}
      //input time for T3 milliseconds
      if (millis() < time_now + T3/potentiometer) {
        // do nothing, waiting user to finish inputs
        getUserMoves();
        buttonLeds->polling(true);
        //Serial.println("waiting for result");
      } else {
        //exsamination of the inputs
        noInterrupts();
        if (wereUserInputsCorrect()) {
          Serial.write("new game");
          score += GAME_REWARD*potentiometer;
          Serial.println(String("New point! Score: ") + score);
          gameState = DURING_GAME;
          

        } else {
          penalty++;
          Serial.println("Penalty!");
          digitalWrite(redLedPin, HIGH);
          //delay(3000);
          gameState = DURING_GAME;
          if (penalty == 3) {
            Serial.println(String("Game Over. Final Score: ") + score);
            gameState = WELCOME;
            penalty = 0;
          }
        }
        resetInput();
        interrupts();
      }

      break;
    case SLEEPMODE:  //sleepmode
      //interrupts();
      configureCommon();
      turnOffLeds();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      /*during deep sleeping mode*/

      sleep_disable();
      gameState = WELCOME;
      break;
    case WAKING_STATE:  //wking state
      /** The program will continue from here. **/
      //Serial.println("WAKE UP");
      /* First thing to do is disable sleep. */
      //wake();
      //gameState = WELCOME;
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
    // Serial.print(String(" ") + sequence[i]);
  }
  //Serial.println("");
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
  if (*currIntensity == 0 || *currIntensity == 200) {
    *fadeAmount = -*fadeAmount;
  }
  // Serial.println(String("in function: ") + *currIntensity);

  //Serial.println(String("in function2: ") + *fadeAmount);
  //Serial.println(gameState);
  delay(10);
}
bool resetInput() {
  for (int i = 0; i < NLED; i++) {
    buttonStates[i] = 0;
  }
}
/*check whether the user was able to recreate the lighting sequence*/
bool wereUserInputsCorrect() {
  Serial.println("user input:");
  for (int i = 0; i < NLED; i++) {

    Serial.print(buttonStates[i] + String(" "));
  }
  Serial.println("");

  Serial.println("sequenze generated");
  for (int i = 0; i < NLED; i++) {
    Serial.print(sequence[i] + String(" "));
  }
  Serial.println("");

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
    //Serial.print(buttonStates[i] + String(" "));
  }
  //Serial.println("");
}



//here i should apply penalty to user when he touches any buttons
void applayPenaltyToUserForAnyInputs() {
}

void configureCommon() {  //any pressed button
  pinMode(WAKE_UP_PIN, INPUT_PULLUP);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
    //digitalWrite(buttonPins[i], LOW);
  }
}
void configureDistinct() {  // distinct button are recognized when pressed
  pinMode(WAKE_UP_PIN, OUTPUT);
  digitalWrite(WAKE_UP_PIN, HIGH);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}
void press() {
  int buttonPressed = digitalRead(WAKE_UP_PIN);
  // debouncing
  delay(20);
  Serial.println("button pressed!");
  if (!interruptStatePressed) {
    if (!buttonPressed) {
      interruptStatePressed = true;
      //
      gameState = GAME_START;
    }
  } else {
    if (!buttonPressed) {
      interruptStatePressed = false;
    }
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