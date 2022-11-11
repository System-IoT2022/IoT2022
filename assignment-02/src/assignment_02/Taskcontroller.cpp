#include "Taskcontroller.h"
#define MAX_TASKS 10
#define NORMALCHECK 1000
#define PREALARMCHECK 500
#define ALARMCHECK 250
#define NORMALWATERLEVEL 1
#define PREALARMWATERLEVEL 1
#define ALARMWATERLEVEL 1



bool TaskController::addTask(BridgeTask* task) {
  if (this->nTasks < MAX_TASKS - 1) {
    taskList[this->nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void TaskController::init(int period) {
  Task::init(period);
  BridgeTask* t0 = new NormalTask();//create constructor for LB pin and LC pin
  this->addTask(t0);
  t0->init(NORMALCHECK);

  Task* t1 = new PreAlarmTask();
  this->addTask(t1);
  t1->init(PREALARMCHECK);

  Task* t2 = new AlarmTask();
  t2->init(ALARMCHECK);
  this->addTask(t2);
  this->setActive(true);
}
void TaskController::execute() {
  
  STATE newstate;

  //check sonar distance

  int level = 0;
  if (level >= ALARMWATERLEVEL) {
    newstate = ALARM;
    Task::changeFrequency(NORMALCHECK);
  } else {
    if (level >= PREALARMWATERLEVEL) {
      newstate = PREALARM;
      Task::changeFrequency(PREALARMCHECK);
    } else {
      newstate = NORMAL;
      Task::changeFrequency(ALARMCHECK);
    }
  }
  if (newstate != this->waterState) {
    this->taskList[this->waterState]->setActive(false);
    this->waterState=newstate;
    switch (this->waterState) {
      case ALARM:
        this->taskList[ALARM]->setActive(true);
        break;
      case PREALARM:
        this->taskList[PREALARM]->setActive(true);
        break;
      case NORMAL:
        this->taskList[NORMAL]->setActive(true);
        break;
    }
  }
  this->taskList[this->waterState]->updateWaterLevel(level);
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask(){
  return this->nTasks;
}