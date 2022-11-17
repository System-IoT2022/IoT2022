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
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

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


#endif