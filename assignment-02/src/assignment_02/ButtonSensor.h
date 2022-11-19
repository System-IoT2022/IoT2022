#ifndef __BUTTONSENSOR__
#define __BUTTONSENSOR__

class ButtonSensor {

public:
  virtual void polling() = 0;
  virtual bool isButtonPressed() = 0;
  virtual void setButtonState(bool state) = 0;
};
#endif