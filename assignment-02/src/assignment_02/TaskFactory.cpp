#include "HardwareSerial.h"
#include "Arduino.h"
#include "TaskFactory.h"
#include "Config.h"
#include "Scheduler.h"


//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
ServoMotor* pMotor;
int pos = 0;
int delta = 1;

void NormalTask::init(int period) {
  Task::init(period);
  this->ledB = new Led(LED_LB_PIN);
}
void NormalTask::execute() {

  // the green led LB is on and LC is off – it means that the bridge can be used.
}

void NormalTask::updateWaterLevel(double waterLevel){};
void NormalTask::setActive(bool active) {
  Task::setActive(active);

  active ? this->ledB->switchOn() : this->ledB->switchOff();
}


void PreAlarmTask::init(int period) {
  Task::init(period);
  this->blinking = new BlinkTask(LED_LC_PIN);  //blinking led LC
  this->blinking->init(1000);                  //led blink of 2seconds
  Scheduler::addTask(this->blinking);
}

void PreAlarmTask::execute() {
  //The red led LC starts blinking with a period of 2 seconds.
  //The LCD is turned on, informing about the pre-alarm and displaying the current water level
  //BridgeTask::waterLevel;
}

void PreAlarmTask::setActive(bool active) {

  this->blinking->setActive(active);

  Task::setActive(active);
}


void AlarmTask::init(int period) {
  Task::init(period);
  pMotor = new ServoMotorImpl(SERVO_MOTOR_PIN);
  this->humanTask = new HumanControllerTask(pMotor);
  this->humanTask->init(PERIOD);
  Scheduler::addTask(this->humanTask);
  this->ledB = new Led(LED_LB_PIN);
  this->ledC = new Led(LED_LC_PIN);
  this->button = new ButtonImpl(BUTTON_B_PIN);
}
void AlarmTask::setActive(bool active) {
  if (active) {
    this->ledC->switchOn();
  } else {
    this->humanTask->setActive(active);
    this->ledB->switchOff();
    this->ledC->switchOff();
    this->button->setButtonState(false);
  }
  Task::setActive(active);
}

void AlarmTask::execute() {
  /*
  The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
  */
  //if button pressed HumanControllerTask->active
  if (!this->humanTask->isActive()) {
    /*
    The valve must be opened of some ALPHA degrees ( 0 < ALPHA < 180), 
    whose value linearly depends on the the current water level, WL2 and WLMAX 
    (so 0 degrees corresponds to WL2 and 180 degrees correspond to WLMAX).
    The opening of the valve changes dynamically depending on the current water level

    otherwise the valve will be open by potentiometer in the humanTask

  */
  }
  button->polling();
  this->humanTask->setActive(button->isButtonPressed());
}


HumanControllerTask::HumanControllerTask(ServoMotor* pMotor) {
  this->pMotor = pMotor;
  angleValue = analogRead(POT_PIN);
}

void HumanControllerTask::init(int period) {
  Task::init(period);
}
void HumanControllerTask::execute() {
  //check potentiometer for motor
  int val = analogRead(POT_PIN);
  if (val != angleValue) {
    angleValue = val;
    val = map(val, 0, 1023, 0, 180);  // scale it to use it with the servo (value between 0 and 180)
    this->pMotor->on();
    this->pMotor->setPosition(val);
    this->pMotor->off();
  }
}

void HumanControllerTask::setActive(bool active) {
  Task::setActive(active);
  active ? this->pMotor->on() : this->pMotor->off();
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
  if (!active) {
    this->ledA->switchOff();
  } else {
    this->ledA->switchOn();
  }
}




void LigthningSubSystemTask::init(int period) {
  Task::init(period);
  pir = new PirImpl(PIR_PIN);
  /*
  lcd.init();
  lcd.backlight();*/
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