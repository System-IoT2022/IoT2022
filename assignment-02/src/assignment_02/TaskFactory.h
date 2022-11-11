#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "BlinkTask.h"
#include "InnestedTask.h"
#include "BridgeTask.h"




class NormalTask : public BridgeTask {
public:
  void init(int period);
  void execute();
  void updateWaterLevel(double waterLevel);
};



class PreAlarmTask : public BridgeTask {
private:
  int pin = 0;
  BlinkTask* blinking;
  enum { ON,
         OFF } state;
public:
  void init(int period);
  void setBlinkingPin(int pin);
  void execute();
  bool updateAndCheckTime(int basePeriod);
};



class AlarmTask : public BridgeTask {
private:
  Task* humanTask;
public:
  bool updateAndCheckTime(int basePeriod);
  void setActive(bool active);
  void init(int period);
  void execute();
};


class LigthningSubSystemTask : public Task {
private:

public:
  void init(int period);
  void execute();
};

class HumanControllerTask : public InnestedTask {
public:
  void init(int period);
  void routine();
};


#endif