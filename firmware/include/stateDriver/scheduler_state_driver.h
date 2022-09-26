
#ifndef INCLUDE_SCHEDULER_STATE_DRIVER_H_
#define INCLUDE_SCHEDULER_STATE_DRIVER_H_

#include "hal.h"
#include "state_driver.h"
#include "modbusRegister.h"
#include <terminal_write.h>


void schStateDriverStart(void);
void whatToDo(msg_t received_msg);

#endif
