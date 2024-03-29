
// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <hal.h>
#include <ch.h>
#include <chprintf.h>
#include <tests.h>

// List of all possible programs
#define MAIN_ROUTINE              0
#define CAN_TEST                  1
#define I2C_TEST                  2
#define SENSOR_M3421_TEST         3
#define CURRENT_SENSOR_TEST       4
#define MODBUSTCP_TEST            5
#define INTERRUPT_WITH_TIMER_TEST 6
#define MOTOR_TEST                7
#define STATE_DRIVER_TEST         8

// Selection of program to run
#define PROGRAM_ROUTINE STATE_DRIVER_TEST

#endif /* INCLUDE_COMMON_H_ */
