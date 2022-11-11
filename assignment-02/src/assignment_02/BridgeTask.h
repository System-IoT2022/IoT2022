#ifndef __BRIDGETASK__
#define __BRIDGETASK__
#include "Task.h"

class BridgeTask : public Task {
  protected:
  double waterLevel;
public:
  virtual void updateWaterLevel(double waterLevel);
};

#endif