#include <manualControl.h>
thread_t * th_manualControl;
/**
 * @brief   Motor speed change function without regulator.
 *
 * @api
 */
static THD_FUNCTION(manualControlThread,arg) {
  (void)arg;
  int16_t required_speed=0;
  systime_t time = chVTGetSystemTime();
  while(!chThdShouldTerminateX()){

    //read the speed set by the user (set in the range -24 +24)
    required_speed = MB_READ_REG_INT16(DATA_MOTOR_REQUIRED_SPEED);

    //Conversion of the user speed in the range -24..+24 to -9500..9500
    MB_WRITE_REG_INT16(DATA_MOTOR_REQUIRED_VOLTAGE,VOLTAGE_TO_ROTATE(required_speed));
    MB_WRITE_REG_INT16(DATA_MOTOR_CURRENT_SPEED,required_speed);

    time = chThdSleepUntilWindowed( time, time + TIME_MS2I(MB_READ_REG_INT16(DATA_CONTROL_TIME)) );
   }

  MB_WRITE_REG_INT16(DATA_MOTOR_REQUIRED_VOLTAGE,0);
  MB_WRITE_REG_INT16(DATA_MOTOR_CURRENT_SPEED,0);
    chThdExit(MSG_OK);
}

/**
 * @brief   Initialization of motor control without a regulator.
 *
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @init
 */
msg_t manualControlInit(void *arg)
{
  arg=arg;
  th_manualControl=chThdCreateFromHeap(NULL,512,"manualControllMotor",NORMALPRIO,manualControlThread, NULL);
  return MSG_OK;
}

/**
 * @brief   Motor control stop without regulator.                     .
 *
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @init
 */
msg_t manualControlUninit(void)
{
  chThdTerminate(th_manualControl);
  msg_t msg=chThdWait(th_manualControl);
  return msg;
}


