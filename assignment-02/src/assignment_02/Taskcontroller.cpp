#include "Taskcontroller.h"
#include <TimerOne.h>
#pragma once
#define MAX_TASKS 10

bool TaskController::addTask(Task* task){
  if (this->nTasks < MAX_TASKS-1){
    taskList[this->nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}

void TaskController::init(int period){
  Task::init(period);
  //add task
}

void TaskController::execute(){
  return;
}
Task** TaskController::getTask(){
  return this->taskList;
}