
#define inputPin 2
#define led1 5
#include "ButtonLed.h"

const int numInteractions = 4;
int pinL[numInteractions] = {5, 6, 7, 8};
int pinB[numInteractions] = {2, 11, 12, 13};
ButtonLed *p;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  p   = new ButtonLed(pinB, pinL, numInteractions);
  p->init(INPUT_PULLUP);
}


void loop() {
  p->polling();

  
}
