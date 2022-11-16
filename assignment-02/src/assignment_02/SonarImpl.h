#include "Sonar.h"

class SonarImpl: public SonarSensor {

public: 
  SonarImpl(const int trigPin, const int echoPin);
  float getDistance();
private:
  const float vs = 331.45 + 0.62*20;
  int trigPin;
  int echoPin;
};
