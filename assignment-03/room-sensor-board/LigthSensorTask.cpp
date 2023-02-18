#include "Scheduler.h"
#include "Config.h"

void LigthSensorTask::init(int period) {
  Task::init(period);
  this->lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
  Scheduler::addTask(this->ledATask);
}

void LigthSensorTask::execute() {

  if (this->lightSensor->getLightIntensity() <= THL) {
    //mqtt message
  }
}