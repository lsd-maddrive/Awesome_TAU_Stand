#include "lld_i2c.h"
#include <terminal_write.h>


void test_i2c(void){
  chSysInit();
  halInit();
  debugStreamInit();
  i2cStartUp();

  uint8_t txbuf[5] = {0xA0, 0x0F, 0x00, 0x01, 0x30};
  uint8_t rxbuf[6] = {0};
  uint8_t data_reg = 0b10101000;
  i2cSimpleWrite(0b1101010, txbuf, 5);
  dbgPrintf("start\r\n");

  while(true){
    i2cRegisterRead(0b1101010, data_reg, rxbuf, 6);
    int16_t* temp = (int16_t*)rxbuf;
    dbgPrintf("x %d, y %d, z %d\r\n", temp[0], temp[1], temp[2]);

    chThdSleepMilliseconds(1000);
  }
}
