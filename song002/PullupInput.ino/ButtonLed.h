#ifndef _BUTTONLED_H_
#define _BUTTONLED_H_
class ButtonLed{
    private:
    int* inputPins;
    int* ledPins;
    int length;

  public:
    ButtonLed(int input[], int output[], int len);
    void init(int inputMode);
    void polling();
    ~ButtonLed(){
        delete[] inputPins;
        delete[] ledPins;
      }
  };
#endif