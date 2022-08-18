#include <terminal_write.h>
#include <encoder.h>


void test_can(void){
  halInit();
  chSysInit();
  encoderInit();
  debugStreamInit();
  dbgPrintf("Start\r\n");

  while(true){

    dbgPrintf("Speed = %.5f\r\n",getVelocity());
    dbgPrintf("Number of turns = %d\r\n",getNumberOfTurns());
    dbgPrintf("Angle = %.5f\r\n",getAngle());
    dbgPrintf("Multi turn angle = %.5f\r\n",getMultiTurnAngle());

    chThdSleepMilliseconds(100);
  }
}



