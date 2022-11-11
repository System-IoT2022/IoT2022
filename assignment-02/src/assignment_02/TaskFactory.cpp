#include "TaskFactory.h"


void NormalTask::init(int period) {
  Task::init(period);
}
void NormalTask::execute() {
  // the green led LB is on and LC is off – it means that the bridge can be used.
}





void PreAlarmTask::init(int period) {
  Task::init(period);
}
void PreAlarmTask::execute() {
  //The red led LC starts blinking with a period of 2 seconds.
  //The LCD is turned on, informing about the pre-alarm and displaying the current water level
}




void AlarmTask::init(int period) {
  Task::init(period);
  this->humanTask= new HumanControllerTask();
}
void AlarmTask::setActive(bool active) {
  if (!active) {
    this->humanTask->setActive(false);
  }
  Task::setActive(false);
}
void AlarmTask::execute() {
  //The green led LB  is turned off and the red led LC is on (without blinking)

  /*
  The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
  */

  //if button pressed HumanControllerTask->active
  /*if(!HumanControllerTask->isActive() )
  The valve must be opened of some ALPHA degrees ( 0 < ALPHA < 180), whose value linearly depends on the the current water level, WL2 and WLMAX (so 0 degrees corresponds to WL2 and 180 degrees correspond to WLMAX). The opening of the valve changes dynamically depending on the current water level
  */
}





void HumanControllerTask::init(int period) {
  Task::init(period);
}
void HumanControllerTask::execute() {
}







void LigthningSubSystemTask::setBlinkingPin(int pin) {
  this->pin = pin;
}

void LigthningSubSystemTask::init(int period) {
  Task::init(period);
  this->led = new Led(this->pin);
  this->state = OFF;
}

void LigthningSubSystemTask::execute() {
  /*check pir[T,F]=> 
    T->
      check ligth[T,F]{
        T->led on
        F->off
      }  
    F-> off
  */
  switch (state) {
    case OFF:
      this->led->switchOn();
      this->state = ON;
      break;
    case ON:  //detected someone
      this->led->switchOff();
      this->state = OFF;
      break;
  }
}