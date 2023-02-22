#include "Taskcontroller.h"
#include "Scheduler.h"
#include "Config.h"

bool TaskController::addTask(RoomTask* task) {
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
  RoomTask* t0 = new LigthTask();  
  this->addTask(t0);
  t0->init(0);
  
  RoomTask* t1 = new rollerBlindTask();
  this->addTask(t1);
  t1->init(0);

  MsgService.init();
}
void TaskController::execute() {
  //get message from bluetooth and serial
  //if from bluetooth send it in serial too
  switch(1){
    case 1:

        this->taskList[0]->setValue(0);
      break;
    case 2: 
        this->taskList[1]->setValue(0);
      break;
  }

  //MsgService.sendMsg(String("waterlevel-") );
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}