#include "Scheduler.h"
#include "Taskcontroller.h"
#include "TaskFactory.h"

void setup(){
  Serial.begin(9600);
  Scheduler::init(250);
  TaskController* t0 = new TaskController();
  t0->init(0);
  Scheduler::addTask(t0);

}

void loop(){
  Scheduler::schedule();
}