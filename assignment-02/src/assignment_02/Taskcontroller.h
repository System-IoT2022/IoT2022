#ifndef __TASKCONTROLLER__
#define __TASKCONTROLLER__
#include "Task.h"
#include "TaskFactory.h"
#pragma once
#define MAX_TASKS 10


class TaskController : public Task {
private:
  int nTasks = 0;
  bool addTask(BridgeTask* task);
  enum STATE{ NORMAL,
         PREALARM,
         ALARM } ;
  STATE waterState;
public:
  BridgeTask* taskList[MAX_TASKS];
  void init(int period);
  void execute();
  Task** getTask();
  int getNTask();
};

#endif