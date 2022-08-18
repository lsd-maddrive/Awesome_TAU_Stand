#include <terminal_write.h>
#include <encoder.h>


void test_can(void){
  halInit();
  chSysInit();
  absoluteEncoderInit();
  debugStreamInit();
  dbgPrintf("Start\r\n");

  while(true){

    dbgPrintf("Speed = %.5f\r\n",getAbsoluteEncoderRotationalSpeed());
    dbgPrintf("Number of turns = %d\r\n",getAbsoluteEncoderNumberOfTurns());
    dbgPrintf("Angle = %.5f\r\n",getAbsoluteEncoderAngleOfRotation());
    dbgPrintf("Multi turn angle = %.5f\r\n",getAbsoluteEncoderMultiTurnAngleOfRotation());

    chThdSleepMilliseconds(100);
  }
}



