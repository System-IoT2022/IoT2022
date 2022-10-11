#ifndef _BUTTONLEDS_H_
#define _BUTTONLEDS_H_
class ButtonLeds {
private:
  int* inputPins;
  int* ledPins;
  int length;

public:
  ButtonLeds(int input[], int output[], int len);
  void init(int inputMode);
  bool polling(bool);
  ~ButtonLeds() {
    delete[] inputPins;
    delete[] ledPins;
  }
};
#endif