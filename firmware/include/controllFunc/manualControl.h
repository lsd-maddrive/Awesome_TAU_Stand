#ifndef INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_
#define INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_

#include <modbusRegister.h>

#define VOLTAGE_TO_PERCENT(speed) (speed+24)*2.083 //Conversion of the user speed in the range -24..+24 to 0..100%

msg_t manualControlInit(void *arg);
msg_t manualControlUninit(void);

#endif
