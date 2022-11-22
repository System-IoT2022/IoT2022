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
  SonarSensor* sonar;
  /*assign enum to waterstate doesn't work runtime
  enum STATE{ NORMAL=0,
         PREALARM=1,
         ALARM=2 } ;*/
  int waterState;
public:
  void init(int period);
  void execute();
  Task** getTask();
  int getNTask();
};

#endif