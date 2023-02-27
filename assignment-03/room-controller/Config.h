
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
#include <Arduino.h>
/*pin of sensors*/
#define SERVO_MOTOR_PIN 11
#define LED_PIN 10
#define BT_RX_PIN 3
#define BT_TX_PIN 2

/*project configurations*/
#define MAX_TASKS 10
#define NORMALCHECK 1000
#define PREALARMCHECK 500
#define PERIOD 1000 


#endif