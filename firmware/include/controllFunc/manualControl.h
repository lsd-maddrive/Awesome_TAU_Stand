#ifndef INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_
#define INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_

#include <modbusRegister.h>

#define VOLTAGE_TO_ROTATE(speed) (speed*396) //Conversion of the user speed in the range -24..+24 to -10 000..10 000

msg_t manualControlInit(void *arg);
msg_t manualControlUninit(void);

#endif
