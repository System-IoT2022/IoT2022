#include <avr/sleep.h>
#include <math.h>
#define WAKE_UP_PIN 2  //external button for waking systems
#define NLED 4
short int state;
int led[4];
int button[4];
int score = 0;
int penalty = 0;
int sequence[NLED];



void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wake, RISING);
  for (int i = 0; i < NLED; i++) {
    led[i] = 10 + i;
    button[i] = 5 + i;
  }
}
void wake() {
  state = 1;
  sleep_disable();
}
void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
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
          state = 3;
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