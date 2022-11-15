#include "TaskFactory.h"
#include "Config.h"

LightSensor* lightSensor; 


void NormalTask::init(int period) {
  Task::init(period);
}
void NormalTask::execute() {
  // the green led LB is on and LC is off – it means that the bridge can be used.
}

void NormalTask::updateWaterLevel(double waterLevel){};






void PreAlarmTask::init(int period) {
  Task::init(period);
  this->state = OFF;
  this->blinking = new BlinkTask(this->pin);  //blinking led LC
  this->blinking->init(2000);                 //led blink of 2seconds
}
void PreAlarmTask::setBlinkingPin(int pin) {
  this->pin = pin;
  this->blinking = new BlinkTask(pin);
}
bool PreAlarmTask::updateAndCheckTime(int basePeriod) {
  Task::updateAndCheckTime(basePeriod);
  this->blinking->updateAndCheckTime(basePeriod);
}

void PreAlarmTask::execute() {
  //The red led LC starts blinking with a period of 2 seconds.
  //The LCD is turned on, informing about the pre-alarm and displaying the current water level
  //BridgeTask::waterLevel;
  
}

void PreAlarmTask::setActive(bool active) {
  if (!active) {
    this->blinking->setActive(false);
  }
  Task::setActive(false);
}




void AlarmTask::init(int period) {
  Task::init(period);
  this->humanTask = new HumanControllerTask();
}
void AlarmTask::setActive(bool active) {
  if (!active) {
    this->humanTask->setActive(false);
  }
  Task::setActive(false);
}
bool AlarmTask::updateAndCheckTime(int basePeriod) {
  BridgeTask::updateAndCheckTime(basePeriod);
  this->humanTask->updateAndCheckTime(basePeriod);
}

void AlarmTask::execute() {
  //The green led LB  is turned off and the red led LC is on (without blinking)

  /*
  The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
  */
  this->humanTask->setActive(true);
  //if button pressed HumanControllerTask->active
  /*if(!HumanControllerTask->isActive() )
  if (this->humanTask->isReady()) {
    this->humanTask->execute();
  }
  The valve must be opened of some ALPHA degrees ( 0 < ALPHA < 180), whose value linearly depends on the the current water level, WL2 and WLMAX (so 0 degrees corresponds to WL2 and 180 degrees correspond to WLMAX). The opening of the valve changes dynamically depending on the current water level
  */
}





void HumanControllerTask::init(int period) {
  Task::init(period);
}
void HumanControllerTask::execute() {
  //check button for river flow control
}








void LigthningSubSystemTask::init(int period) {
  Task::init(period);
  lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
}

void LigthningSubSystemTask::execute() {
  //detected someone
  /*check pir[T,F]=> 
    T->
    {
      lastDetection= NOW()
      check ligth[ligthLevel < LIGTHTHRESHOLD]{
        T->led LA on
        F->off
      } 
    }else{
      after lastDetection-time()>T1 time led LA-> off
    }
  */
  //Serial.println(lightSensor->getLightIntensity());
}