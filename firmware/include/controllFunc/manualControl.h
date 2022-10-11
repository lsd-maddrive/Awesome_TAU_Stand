#ifndef INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_
#define INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_

#include <modbusRegister.h>

#define MANUAL_CONTROLL_TIME 100 //ms
#define SPEED_TO_VOLTAGE(speed) (speed+24)*2.083 //Conversion of the user speed in the range -24..+24 to 0..100%

msg_t manualControlInit(void *arg);
msg_t manualControlUninit(void);

#endif
