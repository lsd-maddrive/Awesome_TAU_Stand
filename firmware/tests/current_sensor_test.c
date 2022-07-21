#include "common.h"
#include "lld_i2c.h"
#include <terminal_write.h>
#include <current_sensor.h>


void test_current_sensor(void){
  chSysInit();
  halInit();
  currentSensorInit();
  debugStreamInit();
  while(true){

    dbgPrintf("Current = %.5f A\r\n", getCurrent());
    chThdSleepMilliseconds(1000);
  }
}

