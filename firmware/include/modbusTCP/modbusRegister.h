#ifndef __MODBUSREGISTER_H
#define __MODBUSREGISTER_H

#include "ch.h"
#include "hal.h"

typedef struct analog_node
{
  struct analog_node* next;
  int16_t value;
  uint8_t address;
}
analog_node_t;

typedef struct discrete_node
{
  struct discrete_node* next;
  uint8_t value;
  uint8_t address;
}
discrete_node_t;


void modbus_analog_register_create(void);
void modbus_discrete_register_create(void);
void modbus_register_create(void);


#endif /* MODBUSREGISTER */
