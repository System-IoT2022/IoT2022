#include "esp32-hal-gpio.h"
#include "Pirimpl.h"
#include "Arduino.h"

PirImpl::PirImpl(int pin){
  this->pin = pin;
  this->detectedStatus = false;
  pinMode(pin, INPUT);
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
    //print(current);
  if (current != detectedStatus ){
    detectedStatus = current;
  }
  return detectedStatus;
}
