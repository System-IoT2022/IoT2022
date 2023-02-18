#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50
/* TO-DO
  create scheduler constructor as static, 
  and using reference instance instead of 
  method static in all of the program 
*/
class Scheduler {
  static int basePeriod;
  static int nTasks;
  static Task* taskList[MAX_TASKS];
  Scheduler(){};//static
public:
  static void init(int basePeriod);
  static bool addTask(Task* task);
  static void schedule();
};

#endif