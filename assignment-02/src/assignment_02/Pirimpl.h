#include "Pir.h"

class PirImpl: public Pir {

public: 
  PirImpl(int pin);
  bool isDetected();
  
private:
  int pin;
  bool detectedStatus;
};