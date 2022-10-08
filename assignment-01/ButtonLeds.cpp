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

    void ButtonLeds::polling(){
      for(int i = 0; i < length; i++){
        int sensor_value = digitalRead(inputPins[i]);
        //debouncing
        delay(20);
        digitalWrite(ledPins[i], sensor_value == LOW ? HIGH : LOW);
      }
    }

    

