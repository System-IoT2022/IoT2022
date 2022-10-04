#define WAKE_UP_PIN 2//external button for waking systems
short int state;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN), wake, RISING); 
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
    // code block
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
