#ifndef INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_
#define INCLUDE_CONTROLLFUNC_MANUALCONTROL_H_

#include <modbusRegister.h>
#include <system_setup.h>

/**
* @brief   Conversion of the user speed in the range -24..+24 to -10 000..10 000.
*/
#define VOLTAGE_TO_ROTATE(speed) (speed*396)

msg_t manualControlInit(void *arg);
msg_t manualControlUninit(void);

#endif
