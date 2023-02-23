#include "Taskcontroller.h"
#include "Scheduler.h"
#include "Config.h"

#include "MsgService.h"
#include "MsgServiceBT.h"

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
  RoomTask* ligth = new LigthTask();
  this->addTask(ligth);
  ligth->init(0);

  RoomTask* motor = new rollerBlindTask();
  this->addTask(motor);
  motor->init(0);

  MsgService.init();
}
void TaskController::execute() {
  Msg* msg;
  if (MsgService.isMsgAvailable()) {
    //serial msg
    msg = MsgService.receiveMsg();
  }
  //get message from bluetooth and serial
  if (msgServiceBT.isMsgAvailable()) {
    //bluetooth user msg
    msg = msgServiceBT.receiveMsg();
    MsgService.sendMsg(msg->getContent());
  }
  if (String(msg->getContent()).substring(0, 6) == "light:") {
    int val = String(msg->getContent()).substring(6).toInt();
    val = max(val, 0);
    val = min(val, 255);
    /* NOT TO FORGET: message deallocation */
    this->taskList[0]->setValue(val);
  } else {
    if (String(msg->getContent()).substring(0, 6) == "servo:") {
      int val = String(msg->getContent()).substring(6).toInt();
      val = max(val, 0);
      val = min(val, 180);
      this->taskList[1]->setValue(val);
    }
  }
  if (String(msg->getContent()) == "config") {
    MsgService.sendMsg("light:" + String(this->taskList[0]->getValue()) + ",roller:" ++String(this->taskList[1]->getValue()));
  }
  delete msg;
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}