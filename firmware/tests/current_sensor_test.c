#include "common.h"
#include "lld_i2c.h"
#include <terminal_write.h>
#include <sensor_m3421.h>
#include <math.h>


void test_current_sensor(void){
  sensorM3421Init();
  debugStreamInit();
  while(true){

    dbgPrintf("Vots = %.5f V\r\n", getVolts();
    dbgPrintf("Current = %.5f A\r\n", getCurrent());
    chThdSleepMilliseconds(1000);
  }
}

