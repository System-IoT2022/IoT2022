#include "Arduino.h"
#include "TaskFactory.h"
#include "Config.h"
#include "Scheduler.h"


//ServoMotor* pMotor;
int pos = 0;
int delta = 1;
Led* ledB = new Led(LED_LB_PIN);
Led* ledC = new Led(LED_LC_PIN);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


void NormalTask::init(int period) {
  Task::init(period);
}
void NormalTask::execute() {
  // the green led LB is on and LC is off – it means that the bridge can be used.
  ledB->switchOn();
  ledC->switchOff();
  Serial.println("ciao");
}

void NormalTask::updateWaterLevel(double waterLevel){
};

void PreAlarmTask::init(int period) {
  Task::init(period);
  this->state = OFF;
  this->blinking = new BlinkTask(this->pin);  //blinking led LC
  this->blinking->init(2000);                 //led blink of 2seconds
}
void PreAlarmTask::setBlinkingPin(int pin) {
  this->pin = pin;
  this->blinking = new BlinkTask(pin);
}
bool PreAlarmTask::updateAndCheckTime(int basePeriod) {
  Task::updateAndCheckTime(basePeriod);
  this->blinking->updateAndCheckTime(basePeriod);
}

void PreAlarmTask::execute() {
  //The red led LC starts blinking with a period of 2 seconds.
  //The LCD is turned on, informing about the pre-alarm and displaying the current water level
  //BridgeTask::waterLevel;
}

void PreAlarmTask::setActive(bool active) {
  if (!active) {
    this->blinking->setActive(false);
  }
  Task::setActive(false);
}


void AlarmTask::init(int period) {
  Task::init(period);
  this->humanTask = new HumanControllerTask();
}
void AlarmTask::setActive(bool active) {
  if (!active) {
    this->humanTask->setActive(false);
  }
  Task::setActive(false);
}
bool AlarmTask::updateAndCheckTime(int basePeriod) {
  BridgeTask::updateAndCheckTime(basePeriod);
  this->humanTask->updateAndCheckTime(basePeriod);
}

void AlarmTask::execute() {
  //The green led LB  is turned off and the red led LC is on (without blinking)

  /*
  The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
  */
  this->humanTask->setActive(true);
  //if button pressed HumanControllerTask->active
  /*if(!HumanControllerTask->isActive() )
  if (this->humanTask->isReady()) {
    this->humanTask->execute();
  }
  The valve must be opened of some ALPHA degrees ( 0 < ALPHA < 180), whose value linearly depends on the the current water level, WL2 and WLMAX (so 0 degrees corresponds to WL2 and 180 degrees correspond to WLMAX). The opening of the valve changes dynamically depending on the current water level
  */
}

void HumanControllerTask::init(int period) {
  Task::init(period);
}
void HumanControllerTask::execute() {
  //check button for river flow control
}


void TurnOnLedForSecondsTask::init(int period) {
  Task::init(period);
   this->ledA = new Led(LED_LA_PIN);
}

void TurnOnLedForSecondsTask::execute() {
  this->setActive(false);
}

void TurnOnLedForSecondsTask::setActive(bool active) {
  //thing that will be executed
  Task::setActive(active);
  if (active == false) {
    this->ledA->switchOff();
  } else {
    this->ledA->switchOn();
  }
}




void LigthningSubSystemTask::init(int period) {
  Task::init(period);
  pir = new PirImpl(PIR_PIN);
  /*
  lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
  pMotor = new ServoMotorImpl(SERVO_MOTOR_PIN);
  lcd.init();
  lcd.backlight();
  pMotor->on();
  pMotor->setPosition(0);*/
  this->lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
  this->pir = new PirImpl(PIR_PIN);
  this->ledATask = new TurnOnLedForSecondsTask();
  this->ledATask->init(T1);
  this->ledATask->setActive(true);
  Scheduler::addTask(this->ledATask);

}

void LigthningSubSystemTask::execute() {

  if (pir->isDetected() && this->lightSensor->getLightIntensity() <= THL) {
    this->ledATask->setActive(true);
  }
  //int val = analogRead(POT_PIN);
  //val = map(val, 0, 1023, 0, 180);  // scale it to use it with the servo (value between 0 and 180)
  //pMotor->on();
  //pMotor->setPosition(180 - val);
  //pMotor->off();
  //Serial.println(sonar->getDistance());
  //delay(1000);
  //lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  //lcd.print("Dammi soldi!");
}