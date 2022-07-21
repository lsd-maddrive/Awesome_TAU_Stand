#include "common.h"
#include "lld_i2c.h"
#include <terminal_write.h>
#include <sensor_m3421.h>

void test_sensor_m3421(void){
  chSysInit();
  halInit();
  sensorM3421Init();
  debugStreamInit();
  float volts;
  while(true){
    volts = sensorM3421Read();
    dbgPrintf("Vots = %.5f\r\n", volts);
    chThdSleepMilliseconds(1000);
  }
}




