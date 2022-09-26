#ifndef INCLUDE_CONTROLLFUNC_NONECONTROLL_H_
#define INCLUDE_CONTROLLFUNC_NONECONTROLL_H_

#include <modbusRegister.h>

#define CONTROLL_TIME 100 //ms
#define KOEF_SPEED_TO_VOLTAGE 10

msg_t contrNoneInit(void *arg);
msg_t contrNoneUninit(void);

#endif
