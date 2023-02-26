#include "HardwareSerial.h"
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
 // msgServiceBT.init();
}

/*Elaborate on the messages sent from the server through serial communications*/
void static responseFromServer(){

   if (Serial.available()){
     //this->taskList[0]->setValue(255);
     char data = Serial.read();
    }
  
}
void TaskController::execute() {

  Msg* msg;
  if (MsgService.isMsgAvailable()) {
    //serial msg
    msg = MsgService.receiveMsg();
    this->taskList[0]->setValue(255);
   
  }
  //get message from bluetooth and serial
 /* if (msgServiceBT.isMsgAvailable()) {
    //bluetooth user msg
    msg = msgServiceBT.receiveMsg();
    MsgService.sendMsg(msg->getContent());
  }*/


  if (String(msg->getContent()).substring(0, 6) == "light:") {
    int val = String(msg->getContent()).substring(6).toInt();
   // Serial.println(val);
    val = max(val, 0);
    val = min(val, 1);
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
    MsgService.sendMsg("light:" + String(this->taskList[0]->getValue()) + " roller:" +String(this->taskList[1]->getValue()));
  }
  if(msg!=NULL)
  delete msg;
  return;
}
Task** TaskController::getTask() {
  return this->taskList;
}
int TaskController::getNTask() {
  return this->nTasks;
}