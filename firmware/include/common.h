// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <hal.h>
#include <ch.h>
#include <chprintf.h>
#include <tests.h>

// List of all possible programs

#define MAIN_ROUTINE            0
#define I2C_TEST                1
#define SENSOR_M3421_TEST       2
#define CURRENT_SENSOR_TEST     3
#define CAN_TEST                4
#define CAN_TEST_2              5

// Selection of program to run
#define PROGRAM_ROUTINE INTERAPTION_TEST

#endif /* INCLUDE_COMMON_H_ */
