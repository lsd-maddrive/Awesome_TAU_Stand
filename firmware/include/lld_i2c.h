
#ifndef INCLUDE_LLD_I2C_H_
#define INCLUDE_LLD_I2C_H_
#include "hal.h"

void i2cStartUp(void);
msg_t i2cSimpleWrite(uint8_t addr, uint8_t *buf, uint8_t n);
msg_t i2cSimpleRead(uint8_t addr, uint8_t *buf, uint8_t n);
msg_t i2cRegisterRead(uint8_t addr, uint8_t raddr, uint8_t *buf, uint8_t n);



#endif /* INCLUDE_LLD_I2C_H_ */
