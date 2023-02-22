#ifndef __ROOMTASK__
#define __ROOMTASK__
#include "Task.h"

class RoomTask : public Task {
  protected:
  int value;
public:
  virtual void setValue(int value);
};

#endif