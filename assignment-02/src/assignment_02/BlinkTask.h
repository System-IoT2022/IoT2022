#ifndef __BLINKTASK__
#define __BLINKTASK__
#include "Led.h"
#include "InnestedTask.h"


class BlinkTask: public InnestedTask {

  int pin;
  Light* led;
  enum { ON, OFF} state;
  void routine();

public:
  
  BlinkTask(int pin);  
  void init(int period);  
};

#endif

