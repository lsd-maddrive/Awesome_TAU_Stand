
#ifndef INCLUDE_SCHEDULER_STATE_DRIVER_H_
#define INCLUDE_SCHEDULER_STATE_DRIVER_H_

#include "hal.h"

#include<system_setup.h>

#include <state_driver.h>
#include <modbusRegister.h>
#include <terminal_write.h>

#define SENSORS_FIRST_FLAG FLAG_CURRENT

void schedulerStart(void);
void whatToDo(msg_t received_msg);

#endif
