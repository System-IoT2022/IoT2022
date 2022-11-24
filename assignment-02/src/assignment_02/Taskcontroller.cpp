#include "Taskcontroller.h"
#include "Scheduler.h"
#include "Config.h"

double rangeConverter(double value, double a1, double b1, double a2, double b2) {
  return (value - a1) / (b1 - a1) * (b2 - a2) + a2;
}

double waterLevelToValveDegree(float val){
    val = rangeConverter(val, ALARMWATERLEVEL, WL_MAX, 0.0, 180.0);  // scale it to use it with the servo (value between 0 and 180)
    val = max(val, 0);
    val = min(val, 180);
    return val;
}


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

  this->smartLightSystem = new LigthningSubSystemTask();
  smartLightSystem->init(T1);
  smartLightSystem->setActive(true);
  Scheduler::addTask(smartLightSystem);
  this->sonar = new SonarImpl(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  this->waterState = 0;
  t0->setActive(true);
  this->setActive(true);
  lcd.init();
  lcd.backlight();
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
        lcd.display();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("state: alarm");
        lcd.setCursor(0, 1);
        lcd.print(String("water level: ") + level + "m");
        lcd.setCursor(0, 2);
      lcd.print(String("valve degree: ") + waterLevelToValveDegree(level) + "*");
        break;
      case PREALARM:
        this->smartLightSystem->setActive(true);
        this->taskList[PREALARM]->setActive(true);
        lcd.display();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("state: pre-alarm");
        lcd.setCursor(0, 2);
        lcd.print(String("water level: ") + level + "m");
        break;
      case NORMAL:
        this->smartLightSystem->setActive(true);
        this->taskList[NORMAL]->setActive(true);
        lcd.clear();
        lcd.noDisplay();
        break;
    }
    this->taskList[this->waterState]->setActive(false);
    this->taskList[newstate]->setActive(true);

    this->taskList[newstate]->updateWaterLevel(level);
    this->waterState = newstate;
  }
  

  //Serial.println(this->waterState);
  Serial.flush();
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}