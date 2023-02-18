#include "PirTask.h"
#include "Scheduler.h"
#include "Config.h"


void PirTask::init(int period) {

  
  Task::init(period);
  

  this->LigthSensor = new LigthSensorTask();
  LigthSensor->init(T1);
  LigthSensor->setActive(false);
  Scheduler::addTask(LigthSensor);
  this->setActive(true);

  //MsgService.init();
}
void PirTask::execute() {
  /*
  bool newState= pir->isDetected();
  if(state!=newState){
    state = newState;
    if(state){
      //mqtt message there are people 
    }
    else{
      //mqtt message there aren't people 
    }
    LigthSensor->setActive(state);
  }
  */
  //MsgService.sendMsg(String("waterlevel-") + level);
  return;
}
Task** PirTask::getTask() {
  return this->taskList;
}
int PirTask::getNTask() {
  return this->nTasks;
}