#include <terminal_write.h>
#include <current_sensor.h>


void test_current_sensor(void){
  chSysInit();
  halInit();
  debugStreamInit();
  dbgPrintf("Current sensor\r\n");
  currentSensorInit();

  while(true){
	palToggleLine(LINE_LED2);
    dbgPrintf("Current = %.5f A\r\n", getCurrent());
    chThdSleepMilliseconds(1000);
  }
}

