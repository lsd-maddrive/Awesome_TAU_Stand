#ifndef __MODBUSREGISTER_H
#define __MODBUSREGISTER_H

#include "ch.h"
#include "hal.h"


#define REGISTER_LEN 100


extern int16_t Analog_Register[REGISTER_LEN];
extern uint8_t Discrete_Register[REGISTER_LEN];



#endif /* MODBUSREGISTER */
