#include "HardwareSerial.h"
#ifndef _TIMER_DELAY_H_
#define _TIMER_DELAY_H_
class TimerDelay {
private:
  int* wait;
  long time_now;
public:
  //imerDelay(){}
  void resetTimer(){
    if(wait != NULL){
      *wait = 0;
    }
  }
  bool delay2(double seconds) {
   // static unsigned int time_now;
    if (wait == NULL) {
      wait = new int(0);
    }
    switch (*wait) {
      case 0:
        time_now = micros();
        *wait = 1;
        //Serial.println("wait");
        break;
      case 1:
        if (micros() < time_now + seconds * 1000000) {
          //do nothing for waiting
        } else {
          //done waiting
          *wait = 2;
          //Serial.println("done waiting");
        }
        break;
    }
    return *wait == 2;
  }
};
#endif