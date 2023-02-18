#ifndef __LIGTHSENSORTASK__
#define __LIGTHSENSORTASK__
#include "Config.h"

class LighSensorTask : public Task {
private:
  LightSensor* lightSensor;
public:
  void init(int period);
  void execute();
};