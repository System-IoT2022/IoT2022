
#include "Pirimpl.h"
#include "LightSensorImpl.h"
#include "Led.h"
#include "Config.h"
#define THL 120
#define LIGHT_SENSOR_PIN 5
#define PIR_SENSOR_PIN 5
#define LED_PIN 5
TaskHandle_t pirSensor;
TaskHandle_t ligthSensor;

bool state;
PirImpl* pir;
LightSensor* lightSensor;
Led* led;




/* pirSensor with priority 1 */
 void pirSensorTask(void* pvParameters) {
  while(1){
  //Serial.println("Pir task");
  client.publish(topic, "0 24.6");  
  delay(1000);
  bool newState = pir->isDetected();
  if (state != newState) {
    state = newState;
    if (state) {
      led->switchOn();
      //mqtt message there are people
      if (ligthSensor == NULL) {
        //TaskCreate(ligthSensorTask, "ligthSensor", 100, NULL, 2, &ligthSensor);
      }
    } else {
      led->switchOff();
      //vTaskDelete(ligthSensor);
      //mqtt message there aren't people
    }
  }
  }
}


/* ligthSensor with priority 2 */
 void ligthSensorTask(void* pvParameters) {
  if (lightSensor->getLightIntensity() <= THL) {
    //mqtt message
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
  xTaskCreatePinnedToCore(pirSensorTask,"pirSensorTask",10000,NULL,1,&pirSensor,0);
  delay(500);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > 3000) {
    lastMsgTime = now;
   // value++;

    value = 1;
    /* creating a msg in the buffer */
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", value);

   
    
    /* publishing the msg */
    client.publish(topic, "1 42.3");  
  }
}