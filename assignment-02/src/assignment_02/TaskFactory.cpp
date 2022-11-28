#include "WString.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "TaskFactory.h"
#include "Config.h"
#include "Scheduler.h"

ServoMotor* pMotor = new ServoMotorImpl(SERVO_MOTOR_PIN);
SonarSensor* sonar = new SonarImpl(SONAR_TRIG_PIN, SONAR_ECHO_PIN);


double rangeConverter(double value, double a1, double b1, double a2, double b2) {
  return (value - a1) / (b1 - a1) * (b2 - a2) + a2;
}

double waterLevelToValveDegree(float val) {
  val = rangeConverter(val, ALARMWATERLEVEL, WL_MAX, 0.0, 180.0);  // scale it to use it with the servo (value between 0 and 180)
  val = max(val, 0);
  val = min(val, 180);
  return val;
}


NormalTask::NormalTask(LiquidCrystal_I2C* lcd) {
  this->lcd = lcd;
}

PreAlarmTask::PreAlarmTask(LiquidCrystal_I2C* lcd) {
  this->lcd = lcd;
}

AlarmTask::AlarmTask(LiquidCrystal_I2C* lcd) {
  this->lcd = lcd;
}

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
  if (active) {
    lcd->clear();
    lcd->noDisplay();
    lcd->noBacklight();
    MsgService.sendMsg("state-normal");
  }
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
  float level = sonar->getDistance();
  lcd->setCursor(13, 1);
  lcd->print(level + String("m"));
}

void PreAlarmTask::setActive(bool active) {
  this->blinking->setActive(active);
  Task::setActive(active);
  if (active) {
    lcd->backlight();
    lcd->display();
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("state: pre-alarm");
    lcd->setCursor(0, 1);
    lcd->print(String("water level: "));
    MsgService.sendMsg("state-prealarm");
  }
}


void AlarmTask::init(int period) {
  Task::init(period);
  this->humanTask = new HumanControllerTask(pMotor, lcd);
  this->humanTask->setActive(false);
  this->humanTask->init(PERIOD);
  Scheduler::addTask(this->humanTask);
  this->ledB = new Led(LED_LB_PIN);
  this->ledC = new Led(LED_LC_PIN);
  this->button = new ButtonImpl(BUTTON_B_PIN);
  valveTask = new TurnOffValveTask();
  valveTask->init(PERIOD);
  Scheduler::addTask(valveTask);
}

void AlarmTask::setActive(bool active) {
  if (active) {
    this->ledC->switchOn();
    pMotor->on();
    lcd->backlight();
    lcd->display();
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("state: alarm");
    lcd->setCursor(0, 1);
    lcd->print(String("water level: "));
    lcd->setCursor(0, 2);
    lcd->print(String("valve degree: "));
    //int str = String("valve-124.24").substring(6).toInt();
    //lcd->print(str);
    MsgService.sendMsg("state-alarm");
  } else {
    this->humanTask->setActive(active);
    this->ledB->switchOff();
    this->ledC->switchOff();
    this->button->setButtonState(false);
    valveTask->setActive(true);
  }
  Task::setActive(active);
}

void AlarmTask::execute() {
  /*
  The LCD is still on, informing about the alarm situation and displaying both the current water level and the opening degrees of the valve 
  */
  float level = sonar->getDistance();

  lcd->setCursor(13, 1);
  lcd->print(level + String("m"));
  lcd->setCursor(14, 2);
  lcd->print(waterLevelToValveDegree(level));
  button->polling();

  float val = sonar->getDistance();
  //Serial.println(String("sonar-") + val);
  //Serial.flush();
  if (!button->isButtonPressed() && !humanTask->isActive()) {
    pMotor->setPosition(waterLevelToValveDegree(val));
  }
  this->humanTask->setActive(button->isButtonPressed());
}


HumanControllerTask::HumanControllerTask(ServoMotor* pMotor, LiquidCrystal_I2C* lcd) {
  this->pMotor = pMotor;
  this->lcd = lcd;
  angleValue = analogRead(POT_PIN);
}

void HumanControllerTask::init(int period) {
  Task::init(period);
  this->remoteControl = false;
}
void HumanControllerTask::execute() {
  /*check message sent from remote*/
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    if (msg->getContent() == "remotecontrol-on") {
      this->remoteControl = true;
    } else if (msg->getContent() == "remotecontrol-off") {
      this->remoteControl = false;
    } else if (String(msg->getContent()).substring(0, 6) == "valve-") {
      val = String(msg->getContent()).substring(6).toInt();
      val = max(val, 0);
      val = min(val, 180);
    /* NOT TO FORGET: message deallocation */
      lcd->setCursor(0, 3);
      lcd->print(msg->getContent());
    }
    delete msg;
  }

  //check potentiometer for motor
  potVal = analogRead(POT_PIN);
  potVal = map(potVal, 0, 1023, 0, 180);

  this->angleValue = this->remoteControl ? val : potVal;
  this->pMotor->setPosition(angleValue);
}


void HumanControllerTask::setActive(bool active) {
  Task::setActive(active);
  //active ? this->remoteControl = false : this->pMotor->off();
  if(!active){
    this->remoteControl = false;
  }
}


void TurnOffValveTask::init(int period) {
  Task::init(period);
}

void TurnOffValveTask::execute() {
  pMotor->setPosition(0);
  if (consumed) {
    pMotor->off();
    Task::setActive(false);
  } else {
    consumed = true;
  }
}

void TurnOffValveTask::setActive(bool active) {
  Task::setActive(active);
  active ? consumed = false : consumed = true;
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
    MsgService.sendMsg("smartlight-off");
  } else {
    this->ledA->switchOn();
    MsgService.sendMsg("smartlight-on");
  }
}




void LigthningSubSystemTask::init(int period) {
  Task::init(period);
  pir = new PirImpl(PIR_PIN);

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
}