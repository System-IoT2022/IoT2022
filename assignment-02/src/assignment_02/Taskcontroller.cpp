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

  lcd.init();
  lcd.backlight();
  Task::init(period);
  BridgeTask* t0 = new NormalTask(&this->lcd);  //create constructor for LB pin and LC pin
  this->addTask(t0);
  t0->init(NORMALCHECK);

  Task* t1 = new PreAlarmTask(&this->lcd);
  this->addTask(t1);
  t1->init(PREALARMCHECK);

  Task* t2 = new AlarmTask(&this->lcd);
  t2->init(ALARMCHECK);
  this->addTask(t2);

  this->smartLightSystem = new LigthningSubSystemTask();
  smartLightSystem->init(T1);
  smartLightSystem->setActive(true);
  Scheduler::addTask(smartLightSystem);
  this->sonar = new SonarImpl(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  this->waterState = 0;
  t0->setActive(true);
  this->setActive(true);

  MsgService.init();
}
void TaskController::execute() {
  int newstate;

  //check sonar
  float level = sonar->getDistance();
  if (level <= ALARMWATERLEVEL) {
    newstate = ALARM;
    Task::changeFrequency(ALARMCHECK);
  } else {
    if (level <= PREALARMWATERLEVEL) {
      newstate = PREALARM;
      Task::changeFrequency(PREALARMCHECK);
    } else {
      newstate = NORMAL;
      Task::changeFrequency(NORMALCHECK);
    }
  }
  if (this->waterState != newstate) {


    switch (newstate) {
      case ALARM:
        this->smartLightSystem->setActive(false);
        this->taskList[ALARM]->setActive(true);
        break;
      case PREALARM:
        this->smartLightSystem->setActive(true);
        this->taskList[PREALARM]->setActive(true);
        break;
      case NORMAL:
        this->smartLightSystem->setActive(true);
        this->taskList[NORMAL]->setActive(true);
        break;
    }
    this->taskList[this->waterState]->setActive(false);
    this->taskList[newstate]->setActive(true);

    this->taskList[newstate]->updateWaterLevel(level);
    this->waterState = newstate;
  }
  MsgService.sendMsg(String("waterlevel-") + level);
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}