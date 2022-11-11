#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;
  bool active;

public:
  virtual void init(int period) {
    myPeriod = period;
    timeElapsed = 0;
    active = false;
  }

  virtual void execute();

  virtual bool updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod) {
      timeElapsed = 0;
      return true;
    } else {
      return false;
    }
  }

  virtual void setActive(bool active) {
    this->active = active;
  }

  void changeFrequency(int period) {
    myPeriod = period;
  }

  bool isActive() {
    return active;
  }
};

#endif