#ifndef __TASKCONTROLLER__
#define __TASKCONTROLLER__
#include "TaskFactory.h"
#define MAX_TASKS 10


class TaskController : public Task {
private:
  int nTasks = 0;
  bool addTask(BridgeTask* task);
  BridgeTask* taskList[MAX_TASKS];
  Task* smartLightSystem;
  
  enum STATE{ NORMAL,
         PREALARM,
         ALARM } ;
  STATE waterState;
public:
  void init(int period);
  void execute();
  Task** getTask();
  int getNTask();
};

#endif