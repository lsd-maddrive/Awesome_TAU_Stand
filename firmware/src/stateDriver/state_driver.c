#include "state_driver.h"

mailbox_t sen_mb;
#define SEN_BUFFER_SIZE 10
msg_t sen_mb_buffer[SEN_BUFFER_SIZE];
/**
 * @brief   Initializes state driver.
 *
 * @param[in] Driver    Structure representing an state driver
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    there were some problems
 *
 * @init
 */
msg_t stateDriverInit(stateDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_UNINIT)
  {
    sdstruct->state = STATE_STOP;
    sdstruct->config.load=NONE_LOAD;
    sdstruct->config.sens=0;
    sdstruct->config.controller.type=MANUAL_CONTROL;
    sdstruct->config.controller.statevariable=0;
    return MSG_OK;
  }
  else return MSG_RESET;
}

/**
 * @brief   Starting the State Driver.
 * @note    Starting a sensor survey.
 *
 * @param[in] sdstruct    structure representing an state driver
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    there were some problems
 *
 * @api
 */
msg_t stateDriverStart(stateDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_STOP)
    {
      chMBObjectInit(&sen_mb, sen_mb_buffer, SEN_BUFFER_SIZE);
      measurementsStart(&sen_mb,&sdstruct->config.sens);
      sdstruct->state = STATE_READY;
        return MSG_OK;
     }
  else return MSG_RESET;
}

/**
 * @brief   Stopping the State driver.
 * @note    Full stop of all working modules.
 *
 * @param[in] sdstruct    Structure representing an state driver
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 * @api
 */
msg_t stateDriverStop(stateDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_READY)
    {
      measurementsStop();
      sdstruct->config.sens = 0;
      sdstruct->state = STATE_STOP;
      return MSG_OK;
    }
  else return MSG_RESET;
}
/**
 * @brief   Switching to the state when the engine is running.
 *
 * @param[in] sdstruct    structure representing an state driver
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t stateDriverActivateMotor(stateDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_READY)
  {
    controllersStart(&sdstruct-> config.controller);
    sdstruct->state = STATE_ACTIVE;
    return MSG_OK;
   }
  else return MSG_RESET;
}

/**
 * @brief   Stopping the motor.
 *
 * @param[in] sdstruct    structure representing an state driver
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t stateDriverDeactivateMotor(stateDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_ACTIVE)
    {
      controllersStop(&sdstruct-> config.controller);
      sdstruct->state = STATE_READY;
      return MSG_OK;
    }
  else return MSG_RESET;
}

/**
 * @brief   Selecting a new load.
 *
 * @param[in] sdstruct    structure representing an state driver
 * @param[in] new_load    new load to be included
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t setNewLoad(stateDriver_t *sdstruct,load_t new_load)
{
  if(sdstruct->state == STATE_STOP || sdstruct->state == STATE_READY)
    {
    sdstruct->config.load=new_load;
      return MSG_OK;
    }
  else return MSG_RESET;
}

/**
 * @brief   Switching on/off the sensor.
 *
 * @param[in] sdstruct    structure representing an state driver
 * @param[in] sen         the sensor that needs to be turned on/off
 * @param[in] step        action on the sensor
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t setNewSen(stateDriver_t *sdstruct,senlist_t sen,senstep_t step){
  if(sdstruct->state == STATE_READY || sdstruct->state == STATE_STOP)
   {
      chMBPostTimeout(&sen_mb, (msg_t)((step<<16)+(sen)), TIME_IMMEDIATE);
      if(step == SEN_ON) sdstruct->config.sens |=(1<<sen);
      else sdstruct->config.sens &=~(1<<sen);

     return MSG_OK;
    }
   else return MSG_RESET;
}

/**
 * @brief   Selecting a new controller.
 *
 * @param[in] sdstruct          structure representing an state driver
 * @param[in] new_controll      new controller to be included
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t setNewControll(stateDriver_t *sdstruct,contrlist_t new_controll)
{
  if(sdstruct->state == STATE_STOP || sdstruct->state == STATE_READY)
    {
      sdstruct->config.controller.type=new_controll;
      return MSG_OK;
    }
  else return MSG_RESET;
}

/**
 * @brief   Changes to the controller parameters.
 *
 * @param[in] sdstruct                structure representing an state driver
 * @param[in] new_param_controll      new controller parameter
 * @param[in] step                    action on the parameter
 *
 * @return              The operation status
 * @retval MSG_OK       if the function succeeded
 * @retval MSG_RESET    there were some problems
 *
 *
 * @api
 */
msg_t setNewParamControll(stateDriver_t *sdstruct,uint8_t new_param_controll,variablestep_t step)
{
  if(sdstruct->state == STATE_STOP || sdstruct->state == STATE_READY)
    {
      if(step==TRUE)sdstruct->config.controller.statevariable|=(1<<new_param_controll);
      else sdstruct->config.controller.statevariable &=~(1<<new_param_controll);

      return MSG_OK;
    }
  else return MSG_RESET;
}

msg_t setNewRequiredSpeed(stateDriver_t *sdstruct,int16_t required_speed)
{
  if(sdstruct->state == STATE_STOP || sdstruct->state == STATE_READY || sdstruct->state == STATE_ACTIVE )
      {
        switch(sdstruct->config.controller.type)
        {
        case MANUAL_CONTROL:
          if(required_speed>=-24 && required_speed<=24) return MSG_OK;
          else return MSG_RESET;
            break;
        case SLAVE_CONTROL:
          if(required_speed>=-1000 && required_speed<=1000)return MSG_OK;
          else return MSG_RESET;
          break;
        default:
        	return MSG_RESET;
        	break;
        }
      }
    else return MSG_RESET;
}
