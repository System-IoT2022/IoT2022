#ifndef __TASKCONTROLLER__
#define __TASKCONTROLLER__
#include "Task.h"
#pragma once
#define MAX_TASKS 10


class TaskController : public Task {
private:
  int nTasks = 0;
  bool addTask(Task* task);
  enum { NORMAL,
         PREALARM,
         ALARM } waterState;
public:
  Task* taskList[MAX_TASKS];

  void init(int period);
  void execute();
  Task** getTask();
};

#endif