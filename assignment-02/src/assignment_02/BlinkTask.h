#ifndef __BLINKTASK__
#define __BLINKTASK__
#include "Led.h"
#include "Task.h"


class BlinkTask: public Task {

  int pin;
  Light* led;
  enum { ON, OFF} state;

public:
  BlinkTask(int pin);  
  void execute();
  void init(int period);  
  void setActive(bool active);
};

#endif

