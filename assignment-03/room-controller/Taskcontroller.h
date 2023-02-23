#ifndef __TASKCONTROLLER__
#define __TASKCONTROLLER__
#include "TaskFactory.h"
#include "Config.h"
#define MAX_TASKS 10

class TaskController : public Task {
private:
  int nTasks = 0;
  bool addTask(RoomTask* task);
  RoomTask* taskList[MAX_TASKS];
public:
  void init(int period);
  void execute();
  Task** getTask();
  int getNTask();
};

#endif