#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin) {
  this->pin = pin;
}

void BlinkTask::init(int period) {
  Task::init(period);
  led = new Led(pin);
  state = OFF;
}
void BlinkTask::setActive(bool active) {
  Task::setActive(active);
  if (!active) {
    this->led->switchOff();
    this->state = OFF;
  }
}

void BlinkTask::execute() {
  switch (state) {
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
