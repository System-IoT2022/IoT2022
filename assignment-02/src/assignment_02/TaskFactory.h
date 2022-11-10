#ifndef __TASKFACTORY__
#define __TASKFACTORY__
#include "Task.h"
#include "Led.h"

class NormalTask : public Task {
  /*  
In this situation, the sampling of the water level measure should be done every period PEnormal 
*/

public:
  void init(int period);
  void execute();
};

class PreAlarmTask : public Task {

public:
  void init(int period);
  void execute();
};

class AlarmTask : public Task {

public:
  void init(int period);
  void execute();
};

class HumanControllerTask : public Task {

public:
  virtual void init(int period);
  void execute() = 0;
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