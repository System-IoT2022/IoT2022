#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "BlinkTask.h"
#include "BridgeTask.h"
#include "Config.h"


class NormalTask : public BridgeTask {
private:
  Led* ledA;
  Led* ledB;
public:
  void init(int period);
  void execute();
  void updateWaterLevel(double waterLevel);
  void setActive(bool active);
};



class PreAlarmTask : public BridgeTask {
private:
  BlinkTask* blinking;
public:
  void init(int period);
  void execute();
  void setActive(bool active);
};



class AlarmTask : public BridgeTask {
private:
  Task* humanTask;
  Led* ledC;
  Led* ledB;
  void setHumanTask();
public:
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
private:
  ServoMotor* pMotor;
public:
  HumanControllerTask(ServoMotor* pMotor);
  void init(int period);
  void execute();
  void setActive(bool active);
};


#endif