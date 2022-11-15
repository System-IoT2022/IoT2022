#include "Pirimpl.h"
#include "Arduino.h"

PirImpl::PirImpl(int pin){
  this->pin = pin;
  this->detectedStatus = false;
}

static void print(int current){
  if (current) {
      Serial.println("detected!");  
    } else {
      Serial.println("no more detected.");
    }
}

bool PirImpl::isDetected(){
   int current = digitalRead(this->pin);
  if (current != detectedStatus ){
    detectedStatus = current;
    print(current);
    return true;
  }
  return false;
}
