#include "common.h"
#include "lld_i2c.h"
#include <hal.h>
#include <ch.h>
#include <terminal_write.h>

void test_sensor_m3421(void){
  chSysInit();
  halInit();
  debug_stream_init();
  i2cStartUp();

  uint8_t rxbuf[3] = {0};
  uint8_t setup = 0b00011000;
  uint8_t sign;
  while (true){
    i2cSimpleWrite(0b1101000, &setup, 1);
    dbgprintf("start %d\r\n", i2cGetErrors(&I2CD1));


    i2cSimpleRead(0b1101000, rxbuf, 3);
    int16_t temp = *(int16_t*)rxbuf;
    int16_t val = (rxbuf[0] << 8) | rxbuf[1];
    if (~rxbuf[0]&(1<<7))sign = 0;
    else sign = 1;
    dbgprintf("%d, %d, %d, %d, %d, %d\r\n", rxbuf[0], rxbuf[1], rxbuf[2], temp, val, sign);
    chThdSleepMilliseconds(1000);
  }
}



