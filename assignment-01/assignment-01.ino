#include <avr/sleep.h>
#include <math.h>
#include "ButtonLeds.h"
//#include "TimerOne.h"
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4

#define WAITING_TIME 10000
#define T1 3000
#define T2 3000
#define T3 5000
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
int ledPins[NLED] = {5, 6, 7, 8};
int redLedPin;
int redIntensity;
int buttonPins[NLED] = {2, 11, 12, 13};
int potentiometerPin;
unsigned long time_now;
unsigned long lastPress = 0;
boolean interruptStatePressed;
ButtonLeds *buttonLeds;

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
int potentiometer;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), press, RISING);
  interruptStatePressed = false;
  redIntensity = 0;
  pinMode(redLedPin, OUTPUT);
  gameState = WELCOME;
  buttonLeds = new ButtonLeds(buttonPins, ledPins, NLED);
  buttonLeds->init(INPUT_PULLUP);
  //Timer1.initialize(1000000);
}

void loop() {
  //polling();
  //updateLedStates();
  switch (gameState) {
    case WELCOME:  //initial state
      //noInterrupts();
      Serial.println("Welcome to the Catch the Led Pattern Game. Press Key T1 to Start");
      time_now = millis();
      gameState = USER_INPUT;
      delay(20);
      //configureCommon();
      break;
    case USER_INPUT:  //wait interaction from the user for 10 seconds
      if (millis() < time_now + WAITING_TIME) {
        //analogWrite(redLedPin, currIntensity);

        ledFading(REDLEDPIN, &currIntensity, &fadeAmount);

        buttonLeds->polling();
        Serial.println(millis());

      } else { /*after 10 secodns, go deep sleep mode.*/
        analogWrite(REDLEDPIN, LOW);
        gameState = SLEEPMODE;
      }
      break;
    case GAME_START:  //Game starts!
      configureDistinct();
      gameStart();
      Serial.println("GO");
      gameState = DURING_GAME;
      break;
    case DURING_GAME:  //during game{showing patterns}
      //wait a bit for T1 milliseconds
      turnOffLeds();
      //Serial.println("adsdmasdma");
      //delay(random(T1));
      //show tricks  for T2 milliseconds
      createNewSequence(sequence, 2);
      turnOnLights(sequence);
      updateLedStates();
      ledFading(REDLEDPIN, &currIntensity, &fadeAmount);

      Serial.println(String(" ") + redIntensity);
      delay(random(T2));
      //applayPenaltyToUserForAnyInputs();
      //time_now = millis();
      //gameState = 5;
      break;
    case END_GAME:  //game{user inputs}
      //input time for T3 milliseconds
      turnOffLeds();
      if (millis < time_now + T3) {
        // do nothing, waiting user to finish inputs
      } else {
        //exsamination of the inputs
        if (wereUserInputsCorrect()) {
          score += GAME_REWARD;
          Serial.println(String("New point! Score: ") + score);
        } else {
          penalty += 1;
          Serial.println("Penalty!");
          digitalWrite(redLedPin, HIGH);
          delay(1000);
          if (penalty == 3) {
            Serial.println(String("Game Over. Final Score: ") + score);
            gameState = WELCOME;
            penalty = 0;
          }
        }
      }

      break;
    case SLEEPMODE:  //sleepmode
      interrupts();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      /*during deep sleeping mode*/
      break;
    case WAKING_STATE:  //wking state
      /** The program will continue from here. **/
      Serial.println("WAKE UP");
      /* First thing to do is disable sleep. */
      wake();
      gameState = WELCOME;
      break;
    default:
      break;
  }
}

/*wake up the system during interrupts*/
void wake() {
  gameState = WAKING_STATE;
  sleep_disable();
}

/*read inputs including: buttons, potentionmeter*/
void polling() {
  for (int i = 0; i < NLED; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);
  }
  //potentiometer = digitalRead(potentiometerPin);
}
/*update the light based on the states*/
void updateLedStates() {
  for (int i = 0; i < NLED; i++) {
    uint8_t value = ledStates[i] == 0 ? LOW : HIGH;
    digitalWrite(ledPins[i], value);
  }
}
/*sets the light states*/
void turnOnLights(int sequence[NLED]) {
  for (int i = 0; i < NLED; i++) {
    ledStates[i] = sequence[i];
  }
}
/*a new sequence used for turning on lights*/
void createNewSequence(int sequence[NLED], int range) {
  for (int i = 0; i < NLED; i++) {
    sequence[i] = random(range);
    // Serial.print(String(" ") + sequence[i]);
  }
  //Serial.println("");
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
/*check whether the user was able to recreate the lighting sequence*/
bool wereUserInputsCorrect() {
}


//here i should apply penalty to user when he touches any buttons
void applayPenaltyToUserForAnyInputs() {
}

void configureCommon() {  //any pressed button
  pinMode(WAKE_UP_PIN, INPUT_PULLUP);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
    digitalWrite(buttonPins[i], LOW);
  }
}
void configureDistinct() {  // distinct button are recognized when pressed
  pinMode(WAKE_UP_PIN, OUTPUT);
  digitalWrite(WAKE_UP_PIN, LOW);

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
      gameState=GAME_START;
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
  score = 0;
  penalty = 0;
  gameState = 2;
}
/*turn off all lights*/
void turnOffLeds() {
  for (int i = 0; i < NLED; i++) {
    ledStates[i] = 0;
    redLed = 0;
  }
}