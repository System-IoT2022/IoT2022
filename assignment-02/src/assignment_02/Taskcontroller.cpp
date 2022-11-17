#include "Taskcontroller.h"
#include "Scheduler.h"
#include "Config.h"


bool TaskController::addTask(BridgeTask* task) {
  if (this->nTasks < MAX_TASKS - 1) {
    if (Scheduler::addTask(task)) {
      taskList[this->nTasks] = task;
      nTasks++;
      return true;
    }
  }
  return false;
}

void TaskController::init(int period) {
  Task::init(period);
  BridgeTask* t0 = new NormalTask();  //create constructor for LB pin and LC pin
  this->addTask(t0);
  t0->init(NORMALCHECK);

  Task* t1 = new PreAlarmTask();
  this->addTask(t1);
  t1->init(PREALARMCHECK);

  Task* t2 = new AlarmTask();
  t2->init(ALARMCHECK);
  this->addTask(t2);
  this->setActive(true);

  Task* smartLightSystem = new LigthningSubSystemTask();
  smartLightSystem->init(T1);
  smartLightSystem->setActive(true);
  this->addTask(smartLightSystem);

  this->sonar = new SonarImpl(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
}
void TaskController::execute() {

  STATE newstate;

  //check sonar
  float level = sonar->getDistance();

  if (level <= ALARMWATERLEVEL) {
    newstate = ALARM;
    Task::changeFrequency(NORMALCHECK);
  } else {
    if (level <= PREALARMWATERLEVEL) {
      newstate = PREALARM;
      Task::changeFrequency(PREALARMCHECK);
    } else {
      newstate = NORMAL;
      Task::changeFrequency(ALARMCHECK);
    }
  }

    Serial.println(newstate);
  if (newstate != this->waterState) {
    Serial.flush();
    Serial.println("nuovo stato");
    this->taskList[this->waterState]->setActive(false);
    this->waterState = newstate;
    switch (this->waterState) {
      case ALARM:
        this->taskList[ALARM]->setActive(true);
        this->smartLightSystem->setActive(false);
        break;
      case PREALARM:
        this->taskList[PREALARM]->setActive(true);
        this->smartLightSystem->setActive(true);
        break;
      case NORMAL:
        this->taskList[NORMAL]->setActive(true);
        this->smartLightSystem->setActive(true);
        break;
    }
  }
  this->taskList[this->waterState]->updateWaterLevel(level);
  Serial.flush();
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}