
/*
 *  This header file stores symbols that concerns 
 *  the configuration of the system.
 *
 */
#ifndef __CONFIG__
#define __CONFIG__
// #define __DEBUG__

#include "RoomTask.h"
#include "Led.h"
#include "servo_motor_impl.h"
#include <LiquidCrystal.h>
#include <Arduino.h>
#include "MsgService.h"

/*pin of sensors*/
#define SERVO_MOTOR_PIN 11
#define LED_PIN 10

/*project configurations*/
#define MAX_TASKS 10
#define NORMALCHECK 1000
#define PREALARMCHECK 500
#define PERIOD 500


#endif