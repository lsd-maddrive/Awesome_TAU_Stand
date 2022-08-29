#ifndef __MODBUSGET_H
#define __MODBUSGET_H


int16_t modbustcp_get_tid(uint8_t* data);
int16_t modbustcp_get_pid(uint8_t* data);
int16_t modbustcp_get_len(uint8_t* data);
uint8_t modbustcp_get_uid(uint8_t* data);
uint8_t modbustcp_get_func(uint8_t* data);
int16_t modbustcp_get_address(uint8_t* data);
int16_t modbustcp_get_count(uint8_t* data);
uint8_t modbustcp_get_boll_value(uint8_t* data);
int16_t modbustcp_get_value(uint8_t* data);

#endif /* MODBUSGET */
