#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "Led.h"

class BridgeTask: public Task{
double waterLevel;
public:
  void virtual updateWaterLevel(double waterLevel);
};


class NormalTask : public BridgeTask {
  /*  
In this situation, the sampling of the water level measure should be done every period PEnormal 
*/

public:
  void init(int period);
  void execute();
  void updateWaterLevel(double waterLevel);
};

class PreAlarmTask : public Task {

public:
  void init(int period);
  void execute();
};

class AlarmTask : public BridgeTask {
private:
  Task* humanTask;
public:
  double waterLevel;
  void setActive(bool active);
  void init(int period);
  void execute();
};

class HumanControllerTask : public Task {

public:
  void init(int period);
  void execute();
};

class LigthningSubSystemTask : public Task {
private:
  int pin;
  Light* led;
  enum { ON,
         OFF } state;
public:
  void init(int period);
  void setBlinkingPin(int pin);
  void execute();
};



#endif