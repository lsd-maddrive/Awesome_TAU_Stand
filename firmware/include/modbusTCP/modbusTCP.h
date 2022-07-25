#ifndef __MODBUSTCP_H
#define __MODBUSTCP_H


void modbustcp_init(void);
void modbustcp_start(void);
int modbustcp_go(uint8_t* payload);

#endif /* MODBUSTCP */
