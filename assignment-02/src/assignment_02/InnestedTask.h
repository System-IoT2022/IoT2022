#ifndef __INNESTEDTASK__
#define __INNESTEDTASK__
#include "Task.h"


class InnestedTask : public Task {
private:
  bool ready;
  virtual void routine();
public:
  bool update(int basePeriod);
  bool isReady();
  void execute();
};

#endif