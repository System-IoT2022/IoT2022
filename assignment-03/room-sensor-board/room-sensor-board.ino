#include "Scheduler.h"
#include "PirTask.h"
//#include "Config.h"

void setup(){
  //WI-FI conn
  Serial.begin(9600);
  Scheduler::init(PERIOD);
  //TaskController* t0 = new TaskController();
  Task* pirSensor = new PirTask();
  pirSensor->init(1000);
  /*
  only when pir detect change state
  TAsk* ligthSensor = new Task()
  ligthSensor->init(60000);
  if(true){
    ligthSensor->setActive(true);
  }
  */
  Scheduler::addTask(pirSensor);

}

void loop(){
  Scheduler::schedule();
}