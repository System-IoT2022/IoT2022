#include "Scheduler.h"
#include <TimerOne.h>

extern int Scheduler::basePeriod = 0;
extern int Scheduler::nTasks = 0;
Task* Scheduler::taskList[MAX_TASKS];
volatile bool timerFlag;

void timerHandler(void) {
  timerFlag = true;
}

void Scheduler::init(int basePeriod) {
  Scheduler::basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l * basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  Scheduler::nTasks = 0;
}

bool Scheduler::addTask(Task* task) {
  if (Scheduler::nTasks < MAX_TASKS - 1) {
    Scheduler::taskList[Scheduler::nTasks] = task;
    Scheduler::nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule() {
  while (!timerFlag) {}
  timerFlag = false;

  for (int i = 0; i < Scheduler::nTasks; i++) {
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(Scheduler::basePeriod)) {
      taskList[i]->execute();
    }
  }
}