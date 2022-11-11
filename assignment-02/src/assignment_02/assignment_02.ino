#include "Scheduler.h"
#include "Taskcontroller.h"
#include "TaskFactory.h"
Scheduler sched;

void setup(){

  Serial.begin(9600);
  sched.init(250);
  TaskController* t0 = new TaskController();
  t0->init(0);
  sched.addTask(t0);

  Task* t1 = new LigthningSubSystemTask();
  t1->init(500);
  sched.addTask(t1);
  Task** vec = t0->getTask();
  for(int i=0;i<t0->getNTask();i++){
    sched.addTask(vec[i]);
  }
}

void loop(){
  sched.schedule();
}