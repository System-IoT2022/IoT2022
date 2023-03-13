#include "HardwareSerial.h"
#include "Taskcontroller.h"
#include "Scheduler.h"
#include "Config.h"

#include "MsgService.h"
#include "MsgServiceBT.h"

//#include "MemoryUsage.h"
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
  msgServiceBT.init();
}

void TaskController::execute() {

  /* 
  DECOMENT ONLY TO DEBUG => REQUIRE MEMORY USAGE LIBRARY
  Serial.print("Free memory: ");
  Serial.println(mu_freeRam());
  */
  String message = "";
  if (MsgService.isMsgAvailable()) {
    //serial msg
    Msg* msg = MsgService.receiveMsg();
    message = msg->getContent();
    delete msg;
  }
  //get message from bluetooth and serial
  if (msgServiceBT.isMsgAvailable()) {
    //bluetooth user msg
    Msg* msg = msgServiceBT.receiveMsg();
    message = msg->getContent();
    Serial.println(message);
    MsgService.sendMsg(message);
    delete msg;
  }


  if (message != "") {
    if (String(message).substring(0, 6) == "light:") {
      int val = String(message).substring(6).toInt();
      // Serial.println(val);
      val = max(val, 0);
      val = min(val, 1);
      /* NOT TO FORGET: message deallocation */
      this->taskList[0]->setValue(val);
    } else if (String(message).substring(0, 6) == "servo:") {
      int val = String(message).substring(6).toInt();
      val = max(val, 0);
      val = min(val, 180);
      this->taskList[1]->setValue(val);
    }
    if (String(message) == "config") {
      MsgService.sendMsg("light:" + String(this->taskList[0]->getValue()) + " roller:" + String(this->taskList[1]->getValue()));
    }
  }

  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}