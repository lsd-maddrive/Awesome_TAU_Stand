#include <terminal_write.h>
#include <absolute_encoder.h>
#include <motor_control.h>

static bool flagg = false;

void stop_motor(void* args){
  (void)args;

  flagg = true;
}

void test_can(void){
  halInit();
  chSysInit();
  palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
  palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
  palSetPadCallback(GPIOC, GPIOC_BUTTON, stop_motor, NULL);
  absoluteEncoderInit();
  motorInit();
  debugStreamInit();
  dbgPrintf("Start\r\n");
  setMotorVoltage(5000);

  while(true){
	if (flagg == true) setMotorVoltage(0);
	dbgPrintf("Speed = %.3f\r\n",getAbsoluteEncoderRotationalSpeed());
	dbgPrintf("Number of turns = %d\r\n",getAbsoluteEncoderNumberOfTurns());
	dbgPrintf("Angle = %.5f\r\n",getAbsoluteEncoderAngleOfRotation());
	dbgPrintf("Multi turn angle = %d\r\n",getAbsoluteEncoderMultiTurnAngleOfRotation());

	chThdSleepMilliseconds(50);
  }
}



