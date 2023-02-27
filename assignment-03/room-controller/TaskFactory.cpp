#include "WString.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "TaskFactory.h"
#include "Config.h"
#include "Scheduler.h"





LigthTask::LigthTask() {
  //led
}

rollerBlindTask::rollerBlindTask() {
  this->Motor = new ServoMotorImpl(SERVO_MOTOR_PIN);
}



void LigthTask::init(int period) {
  Task::init(period);
  this->led = new Led(LED_PIN);
  this->value = 0;
}
void LigthTask::execute() {
  //this->setActive(false);
}

void LigthTask::setActive(bool active) {
  Task::setActive(active);
}
void LigthTask::setValue(int value) {
 // Serial.println("receiving light signal");
    this->value = value;
  if (this->value <= 0) {
    this->led->switchOff();
    this->setActive(false);
  } else {
    this->led->switchOn();
    this->setActive(true);
  }
}
int LigthTask::getValue(){
  return this->value;
}


void rollerBlindTask::init(int period) {
  Task::init(period);
}

void rollerBlindTask::execute() {
  //set roller blind

  this->setActive(false);
}
void rollerBlindTask::setValue(int value) {
  if (value == this->value) {
    this->setActive(false);
  } else {
    this->value = value;
    this->setActive(true);
  }
}
void rollerBlindTask::setActive(bool active) {
  Task::setActive(active);
}
int rollerBlindTask::getValue(){
  return this->value;
}
