#include "esp32-hal-gpio.h"
#include "LightSensorImpl.h"
#include "Arduino.h"

LightSensorImpl::LightSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

int LightSensorImpl::getLightIntensity(){
  int value = analogRead(pin);
  return map(value,0,4096,0,255);
   
}
