#include <terminal_write.h>
#include <absolute_encoder.h>


void test_can(void){
  halInit();
  chSysInit();
  absoluteEncoderInit();
  debugStreamInit();
  dbgPrintf("Start\r\n");
  chThdSleepMilliseconds(5000);
  dbgPrintf("Stop\r\n");
      absoluteEncoderUninit();
      dbgPrintf("Speed = %.5f\r\n",getAbsoluteEncoderRotationalSpeed());

  while(true){

    dbgPrintf("Speed = %.5f\r\n",getAbsoluteEncoderRotationalSpeed());
    dbgPrintf("Number of turns = %d\r\n",getAbsoluteEncoderNumberOfTurns());
    dbgPrintf("Angle = %.5f\r\n",getAbsoluteEncoderAngleOfRotation());
    dbgPrintf("Multi turn angle = %d\r\n",getAbsoluteEncoderMultiTurnAngleOfRotation());

    chThdSleepMilliseconds(5000);
    absoluteEncoderUninit();
//    dbgPrintf("Speed = %.5f\r\n",getAbsoluteEncoderRotationalSpeed());
  }
}



