#include"ButtonLeds.h"
#include<Arduino.h>
    ButtonLeds::ButtonLeds(int input[], int output[], int len){
        this->length = len;
        inputPins = new int[len];
        ledPins = new int[len];
        if(!inputPins || !ledPins){
          Serial.println("error on initialization");
          return;
        }
        for(int i = 0; i < len; i++){
            inputPins[i] = input[i];
            ledPins[i] = output[i];
        }

    };

    void ButtonLeds::init(int inputMode){
      for(int i = 0; i < length; i++){
        pinMode(inputPins[i], inputMode);
        pinMode(ledPins[i], OUTPUT);
      }
    }

    bool ButtonLeds::polling(bool mantainState){
      bool on = false;
      for(int i = 0; i < length; i++){
         int sensor_value = digitalRead(inputPins[i]);
        //debouncing
        delay(50);
        if(sensor_value == LOW){
          digitalWrite(ledPins[i], HIGH);
          on = true;
        }else if(!mantainState){
         digitalWrite(ledPins[i], LOW);
        }
      }
      return on;
    }

    

