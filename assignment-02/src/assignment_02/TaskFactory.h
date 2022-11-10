#ifndef __TASKFACTORY__
#define __TASKFACTORY__

class NormalTask : public Task {
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    active = true;
  }

  virtual void execute() = 0; 
};

class PreAlarmTask : public Task {
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    active = true;
  }

  virtual void execute() = 0; 
};

class AlarmTask : public Task {
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    active = true;
  }

  virtual void execute() = 0; 
};

class HumanControllerTask : public Task {
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
    active = true;
  }

  virtual void execute() = 0; 
};



#endif