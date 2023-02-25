
#include "Pirimpl.h"
#include "LightSensorImpl.h"
#include "Led.h"
#include "Config.h"
#include "string.h"

#define THL 255
#define LIGHT_SENSOR_PIN 5
#define PIR_SENSOR_PIN 7
#define LED_PIN 4
TaskHandle_t pirTask;
TaskHandle_t ligthTask;

bool state=false;
PirImpl* pir;
LightSensorImpl* lightSensor;
Led* led;

/* pirSensor with priority 1 */
void pirSensorTask(void* pvParameters) {
  while (1) {
    //Serial.println("Pir task");
    bool newState = pir->isDetected();
    if (state != newState) {
      state = newState;
      if (state) {
        led->switchOn();
        //mqtt message there are people
        client.publish(topic, "presence 1");
      } else {
        led->switchOff();
        //mqtt message there aren't people
        client.publish(topic, "presence 0");
      }
    }
    delay(1000);
  }
}


/* ligthSensor with priority 2 */
void lightSensorTask(void* pvParameters) {
  while (true) {
    if (state) {

      if (lightSensor->getLightIntensity() <= THL) {
        char cstr[3] = "";
        int num = lightSensor->getLightIntensity();
        itoa(num, cstr, 10);
        char str[20] = "brightness ";
        strcat(str, cstr);
        client.publish(topic, str);
      }
    }
    delay(1000);
  }
}

void setup() {
  //WI-FI conn
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  state = false;
  pir = new PirImpl(PIR_SENSOR_PIN);
  led = new Led(LED_PIN);
  lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
  xTaskCreatePinnedToCore(pirSensorTask, "pirSensorTask", 10000, NULL, 1, &pirTask, 0);
  delay(500);
  xTaskCreatePinnedToCore(lightSensorTask, "lightSensorTask", 10000, NULL, 1, &ligthTask, 1);
  delay(500);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //client.loop_forever(); //not implemneted for esp32 
  unsigned long now = millis();
  if (now - lastMsgTime > 3000) {
    lastMsgTime = now;
    // value++;

    value = 1;
    /* creating a msg in the buffer */
    snprintf(msg, MSG_BUFFER_SIZE, "%ld", value);



    /* publishing the msg */
    //client.publish(topic, "1 42.3");
  }
}