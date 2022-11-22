/*
 *  This header file stores symbols that concerns 
 *  the configuration of the system.
 *
 */
#ifndef __CONFIG__
#define __CONFIG__
// #define __DEBUG__

#include "LightSensorImpl.h"
#include "Pirimpl.h"
#include "Led.h"
#include "SonarImpl.h"
#include "servo_motor_impl.h"
#include <LiquidCrystal.h>
#include <Arduino.h>
#include "ButtonImpl.h"

/*pin of sensors*/
#define LED_LA_PIN 4
#define LED_LB_PIN 5
#define LED_LC_PIN 6
#define BUTTON_B_PIN 2
#define PIR_PIN 8

#define POT_PIN A0
#define LIGHT_SENSOR_PIN A1

#define SONAR_ECHO_PIN 9
#define SONAR_TRIG_PIN 10
#define SERVO_MOTOR_PIN 11


/*project configurations*/
#define MAX_TASKS 10
#define NORMALCHECK 1000
#define PREALARMCHECK 500
#define ALARMCHECK 250
#define THL 30   //thresh hold for light sensor
#define T1 2000  // 2 seconds

//to do
#define NORMALWATERLEVEL 1
#define PREALARMWATERLEVEL 0.30
#define ALARMWATERLEVEL 0.15
#define WL_MAX 0.05
#define NORMAL 0
#define PREALARM 1
#define ALARM 2
#define PERIOD 500

#endif