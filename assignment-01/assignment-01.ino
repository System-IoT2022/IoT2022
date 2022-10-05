#include <avr/sleep.h>

#define WAKE_UP_PIN 2//external button for waking systems
short int state;
int led[4];
int button[4];
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wake, RISING); 
  for(int i=0;i<4;i++){
      led[i]=10+i;
      button[i]=6+i;
  }
}
void wake(){
  state = 1;
  sleep_disable();
  
} 
void loop() {
  // put your main code here, to run repeatedly:
  switch(state) {
    case 1://initial state
      noInterrupts();
    // new sequence list

      break;
    case 2:
    // code block
      break;
    default://sleepmode
    interrupts();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    // create new sequence
    //
  }

}
