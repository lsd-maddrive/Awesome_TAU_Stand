#ifndef __MODBUSTCP_H
#define __MODBUSTCP_H

#include "ch.h"
#include "hal.h"

void modbustcp_init(void);
void modbustcp_start(void);
int16_t modbustcp_go(uint8_t* data);

#endif /* MODBUSTCP */
