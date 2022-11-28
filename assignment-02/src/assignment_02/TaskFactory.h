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
  LiquidCrystal_I2C* lcd;
public:
  NormalTask(LiquidCrystal_I2C* lcd);
  void init(int period);
  void execute();
  void updateWaterLevel(double waterLevel);
  void setActive(bool active);
};



class PreAlarmTask : public BridgeTask {
private:
  BlinkTask* blinking;
  LiquidCrystal_I2C* lcd;
public:
  PreAlarmTask(LiquidCrystal_I2C* lcd);
  void init(int period);
  void execute();
  void setActive(bool active);
};

class TurnOffValveTask : public Task {
private:
  bool consumed;
public:
  void init(int period);
  void execute();
  void setActive(bool active);
};

class AlarmTask : public BridgeTask {
private:
  Task* humanTask;
  TurnOffValveTask * valveTask;
  Led* ledC;
  Led* ledB;
  ButtonSensor* button;
  //SonarSensor* sonar;
  LiquidCrystal_I2C* lcd;
public:
  AlarmTask(LiquidCrystal_I2C* lcd);
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
  int angleValue;
  bool remoteControl;
   LiquidCrystal_I2C* lcd;
   int val = 0, potVal = 0;
public:
  HumanControllerTask(ServoMotor* pMotor, LiquidCrystal_I2C* lcd);
  void init(int period);
  void execute();
  void setActive(bool active);
};


#endif