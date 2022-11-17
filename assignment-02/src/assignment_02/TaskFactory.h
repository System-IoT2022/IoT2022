#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "BlinkTask.h"
#include "BridgeTask.h"
#include "Config.h"

class NormalTask : public BridgeTask {
  private:
    Led* ledA;
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
  void setActive(bool active);
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
  Task* ledATask;
  LightSensor* lightSensor;
  Pir* pir;
public:
  void init(int period);
  void execute();
};

class TurnOnLedForSecondsTask : public Task {
  private:
    Led* ledA;
  public:
  void init(int period);
  void execute();
  void setActive(bool active);
};

class HumanControllerTask : public Task {
public:
  void init(int period);
  void execute();
};


#endif