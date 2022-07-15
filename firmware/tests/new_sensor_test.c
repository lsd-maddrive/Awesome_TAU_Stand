#include "common.h"
#include "lld_i2c.h"
#include <terminal_write.h>
#include <sensor_m3421.h>

void new_test(void){
  sensor_m3421_init();
  debug_stream_init();
  float volts;
  while(true){
    sensor_m3421_read();
    volts = get_volts();
    dbgprintf("Vots = %.5f\r\n", volts);
    chThdSleepMilliseconds(1000);
  }
}


