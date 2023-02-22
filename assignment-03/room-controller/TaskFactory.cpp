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
}
void LigthTask::execute() {
  //set ligth
  MsgService.sendMsg("state-normal");
  this->setActive(false);
}

void LigthTask::setActive(bool active) {
  Task::setActive(active);
}
void LigthTask::setValue(int value) {
  if (this->value == value) {
    this->setActive(false);
  } else {
    this->value = value;
    this->setActive(true);
  }
}

void rollerBlindTask::init(int period) {
  Task::init(period);
}

void rollerBlindTask::execute() {
  //set roller blind

  MsgService.sendMsg("state-prealarm");
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
