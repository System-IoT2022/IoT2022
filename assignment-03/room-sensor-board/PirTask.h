#ifndef __PIRTASK__
#define __PIRTASK__
#include "Config.h"
#include "Pirimpl.h"
#define MAX_TASKS 10

class PirTask : public Task {
private:
  int nTasks = 0;
  bool state=false;
  Pirimpl* pir = new Pirimpl();
  Task* LigthSensor;
public:
  void init(int period);
  void execute();
  Task** getTask();
  int getNTask();
};

#endif