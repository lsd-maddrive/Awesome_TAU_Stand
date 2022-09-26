#include <noneControll.h>

/**
 * @brief   Motor speed change function without regulator.
 *
 * @api
 */
static THD_FUNCTION(contrNoneAct,arg) {
  (void)arg;
  float required_speed=0;
  systime_t time = chVTGetSystemTime();
  while(!chThdShouldTerminateX()){

    //read the speed set by the user
    required_speed = MB_READ_REG_FLOAT(DATA_MOTOR_REQUIRED_SPEED);

    MB_WRITE_REG_FLOAT(DATA_MOTOR_REQUIRED_VOLTAGE,required_speed*KOEF_SPEED_TO_VOLTAGE);
    MB_WRITE_REG_FLOAT(DATA_MOTOR_CURRENT_SPEED,required_speed*KOEF_SPEED_TO_VOLTAGE);
    time = chThdSleepUntilWindowed( time, time + TIME_MS2I( CONTROLL_TIME ) );
   }
    chThdExit(MSG_OK);
}

/**
 * @brief   Initialization of motor control without a regulator.                     .
 *
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @init
 */
msg_t contrNoneInit(void *arg)
{
  arg=arg;
  chThdCreateFromHeap(NULL,512,"noneControllMotor",NORMALPRIO,contrNoneAct, NULL);
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
msg_t contrNoneUninit(void)
{
  chThdTerminate((thread_t *)contrNoneAct);
  msg_t msg=chThdWait((thread_t *)contrNoneAct);
  return msg;
}


