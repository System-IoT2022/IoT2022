#include "ButtonSensor.h"

#define BOUNCING_TIME 100

class ButtonImpl : public ButtonSensor {
private:
  int pin;
  bool buttonPressed;
  float lastButtonPressedTime;
public:
  ButtonImpl(const int pin);
  bool isButtonPressed();
  void polling();
  void setButtonState(bool state);
};