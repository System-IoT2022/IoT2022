#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin){
  this->pin = pin;    
}
  
void BlinkTask::init(int period){
  Task::init(period);
  Task::setActive(true);
  led = new Led(pin); 
  state = OFF;    
}
  
void BlinkTask::routine(){
  switch (state){
    case OFF:
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}
