#include "Scheduler.h"
#include "Taskcontroller.h"
#include "TaskFactory.h"
//#include "Config.h"

void setup(){
  Serial.begin(9600);
  Scheduler::init(PERIOD);
  TaskController* t0 = new TaskController();
  t0->init(0);
  Scheduler::addTask(t0);

}

void loop(){
  Scheduler::schedule();
}