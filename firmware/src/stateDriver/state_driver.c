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
msg_t stateDriverInit(sdDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_UNINIT)
  {
    sdstruct->state = STATE_STOP;
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
msg_t stateDriverStart(sdDriver_t *sdstruct)
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
msg_t stateDriverStop(sdDriver_t *sdstruct)
{
  if(sdstruct->state == STATE_READY)
    {
      measurementsStop();
      sdstruct->state = STATE_STOP;
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
msg_t setNewLoad(sdDriver_t *sdstruct,load_t new_load)
{
  if(sdstruct->state == STATE_STOP)
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
msg_t setNewSen(sdDriver_t *sdstruct,senlist_t sen,senstep_t step){
  if(sdstruct->state == STATE_READY || sdstruct->state == STATE_ACTIVE || sdstruct->state == STATE_STOP)
   {
    if((sdstruct->config.load & (1<<sen))!=0)
    {
      if(sdstruct->state != STATE_STOP)chMBPostTimeout(&sen_mb, (msg_t)((step<<16)+(sen)), TIME_IMMEDIATE);

      if(step==TRUE)sdstruct->config.sens |=(1<<sen);
      else sdstruct->config.sens &=~(1<<sen);

     return MSG_OK;
    }
    else return MSG_RESET;
   }
   else return MSG_RESET;
}





