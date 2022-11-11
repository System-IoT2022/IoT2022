#include "InnestedTask.h"

bool InnestedTask::update(int basePeriod) {
  if (this->ready = true)
    return true;
  if (Task::updateAndCheckTime(basePeriod)) {
    this->ready = true;
  }
};
void InnestedTask::routine(){return ;};
void InnestedTask::execute() {
  if (this->ready)
    this->routine();
  this->ready = false;
};
bool InnestedTask::isReady() {
  return this->ready;
};