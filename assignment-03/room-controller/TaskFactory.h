#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "RoomTask.h"
#include "Config.h"


class LigthTask : public RoomTask {
private:
  Led* led;
public:
  LigthTask();
  void init(int period);
  void execute();
  void setValue(int value);
  void setActive(bool active);
  int getValue();
};



class rollerBlindTask : public RoomTask {
private:
  ServoMotor* Motor;
public:
  rollerBlindTask();
  void init(int period);
  void execute();
  void setValue(int value);
  void setActive(bool active);
  int getValue();
};

#endif