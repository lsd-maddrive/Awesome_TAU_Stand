#include "slaveControl.h"

thread_t * th_slaveControl;
/**
 * @brief   Motor control function by slave control.
 *
 * @api
 */
static THD_FUNCTION(slaveControlThread,stateVariable) {

  pid_t pid_data={.error_speed={0,0,0,0,0,0},
                  .force_speed={0,0,0},
                  .sum_force=0};
  float required_output=0;
  systime_t time = chVTGetSystemTime();
  while(!chThdShouldTerminateX()){
    required_output=MB_READ_REG_FLOAT(DATA_MOTOR_REQUIRED_SPEED);
    for(uint8_t i=0;i<NUMBER_VARIABLE;i++)
    {
      if((*(uint8_t*)stateVariable & (1<<i))!=0)
      {
        switch(i)
        {
        case VARIABLE_ROTATE:
          pid_data.error_speed.prev=pid_data.error_speed.current;
          pid_data.error_speed.current=required_output-MB_READ_REG_FLOAT(DATA_INC_ENCODER_ROTATIONAL_SPEED);

          //Finding the proportional component of the regulator
          pid_data.force_speed.pr=MB_READ_REG_FLOAT(DATA_CONTR_KP)*pid_data.error_speed.current;
          MB_WRITE_REG_FLOAT(DATA_FORCE_KP,pid_data.force_speed.pr);

          //Finding the differential component of the regulator
          pid_data.error_speed.current_del=pid_data.error_speed.current-pid_data.error_speed.prev;
          pid_data.force_speed.dif=MB_READ_REG_FLOAT(DATA_CONTR_KD)*(pid_data.error_speed.current_del)/(DATA_CONTROL_TIME*0.001);
          MB_WRITE_REG_FLOAT(DATA_FORCE_KD,pid_data.force_speed.dif);

          //Finding the integral component of the regulator
          pid_data.error_speed.sum+=pid_data.error_speed.current;
          if(pid_data.error_speed.sum>pid_data.error_speed.sum_lim)pid_data.error_speed.sum=pid_data.error_speed.sum_lim;
          if(pid_data.error_speed.sum<pid_data.error_speed.sum_lim)pid_data.error_speed.sum=-pid_data.error_speed.sum_lim;
          pid_data.force_speed.integ=MB_READ_REG_FLOAT(DATA_CONTR_KI)*pid_data.error_speed.sum*DATA_CONTROL_TIME*0.001;
          MB_WRITE_REG_FLOAT(DATA_FORCE_KI,pid_data.force_speed.integ);

          //Final reaction of the PID regulator
          pid_data.sum_force=pid_data.force_speed.pr+pid_data.force_speed.dif+pid_data.force_speed.integ;

          break;
        case VARIABLE_CURRENT:
          break;
        }
      }
    }
    MB_WRITE_REG_FLOAT(DATA_FORCE_PID,pid_data.sum_force);

    MB_WRITE_REG_FLOAT(DATA_MOTOR_REQUIRED_VOLTAGE,MB_READ_REG_FLOAT(DATA_MOTOR_REQUIRED_VOLTAGE)+pid_data.sum_force);
    MB_WRITE_REG_FLOAT(DATA_MOTOR_CURRENT_SPEED,MB_READ_REG_FLOAT(DATA_MOTOR_CURRENT_SPEED)+pid_data.sum_force);

    time = chThdSleepUntilWindowed( time, time + TIME_MS2I( DATA_CONTROL_TIME ) );
   }
    chThdExit(MSG_OK);
}

/**
 * @brief   Initialization of motor control using the slave controller.                     .
 *
 * @param[in] stateVariable   mask of state variables
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @init
*/
msg_t slaveControlInit(void* stateVariable)
{
  th_slaveControl=chThdCreateFromHeap(NULL,512,"slaveControllMotor",NORMALPRIO,slaveControlThread, (void *)stateVariable);
  return MSG_OK;
}

/**
 * @brief   Stopping motor control using the slave controller.                     .
 *
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @init
 */
msg_t slaveControlUninit(void)
{
  chThdTerminate(th_slaveControl);
  msg_t msg=chThdWait(th_slaveControl);
  return msg;
}
