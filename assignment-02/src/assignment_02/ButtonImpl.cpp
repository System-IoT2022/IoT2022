#include "ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(const int pin) {
  this->pin = pin;
  pinMode(this->pin, INPUT);
  this->buttonPressed = false;
  this->lastButtonPressedTime = millis();
}

void ButtonImpl::polling(){
   if (digitalRead(this->pin) == HIGH) {
    long ts = millis();
    if (ts - lastButtonPressedTime > BOUNCING_TIME) {
      lastButtonPressedTime = ts;
      int buttonStatus = digitalRead(this->pin);
      if (buttonStatus == HIGH) {
        this->buttonPressed = !this->buttonPressed;
      }
    }
  }
}

void ButtonImpl::setButtonState(bool state){
  this->buttonPressed = state;
}

bool ButtonImpl::isButtonPressed() {
  return buttonPressed;
}