
#define inputPin 2
#define led1 5

class PollUPButtonLed{
  private:
    int* inputPins;
    int* ledPins;
    int length;

  public:
    PollUPButtonLed(int input[], int output[], int len){
        this->length = len;
        inputPins = new int[len];
        ledPins = new int[len];
        Serial.println("sadklass");
        for(int i = 0; i < len; i++){
            inputPins[i] = input[i];
            ledPins[i] = output[i];
            Serial.println(inputPins[i]);
        }
    };

    void init(int inputMode){
      for(int i = 0; i < length; i++){
        pinMode(inputPins[i], inputMode);
        pinMode(ledPins[i], OUTPUT);
      }
    }

    void polling(){
      for(int i = 0; i < length; i++){
        int sensor_value = digitalRead(inputPins[i]);
        if(sensor_value == LOW){
          digitalWrite(ledPins[i], HIGH);
         // Serial.println(sensor_value);
        }else{
           digitalWrite(ledPins[i], LOW);
        }
        //digitalWrite(ledPins[i], sensor_value == LOW ? HIGH : LOW);
      }
    }
    ~PollUPButtonLed(){
      delete[] inputPins;
      delete[] ledPins;
    }



};
const int numInteractions = 4;
int pinL[numInteractions] = {5, 6, 7, 8};
int pinB[numInteractions] = {2, 11, 12, 13};
PollUPButtonLed p = PollUPButtonLed(pinL, pinB, numInteractions);

void setup() {
  // put your setup code here, to run once:
  p.init(INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  p.polling();
  
}
