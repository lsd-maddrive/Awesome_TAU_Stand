#include "measurements.h"

mailbox_t *sensors_mb;

senaction_t sen_table_fun[NUMBER_SENSORS] = {
    [SEN_CURRENT] = {currentSensorInit,currentSensorUninit},
    [SEN_ABS_ENCODER] = {absoluteEncoderInit,absoluteEncoderUninit},
    [SEN_INC_ENCODER] = {incrementalEncoderInterruptInit,incrementalEncoderInterruptUninit},
};

static thread_t *tp_measur;
static THD_WORKING_AREA(waSensContr, 256);
static THD_FUNCTION(sensContr, sens)
{
  senlist_t sen;
  senstep_t step;
  msg_t received_msg;
  for(uint8_t i=0;i<NUMBER_SENSORS;i++)
  {
    if((*(uint16_t*)sens & (1<<i))!=0)sen_table_fun[i].sen_init();
  }
  while(!chThdShouldTerminateX()){
    msg_t msg_mb = chMBFetchTimeout(sensors_mb, &received_msg, TIME_INFINITE);
    if(msg_mb==MSG_OK && received_msg!=-1)
      {
        step=(senstep_t)(received_msg>>16);
        sen=(senlist_t)(received_msg & 0xFF);
        switch (step){
        case SEN_ON:
          sen_table_fun[sen].sen_init();
          break;
        case SEN_OFF:
          sen_table_fun[sen].sen_uninit();
          break;
        }
      }
  }
  for(uint8_t i=0;i<NUMBER_SENSORS;i++)
  {
    if((*(uint16_t*)sens & (1<<i))!=0)sen_table_fun[i].sen_uninit();
  }

  chThdExit(MSG_OK);
}

/**
 * @brief   Initialization and launch of sensor polling.
 *
 * @param[in] get_mb    pointer to the mailbox
 * @param[in] sens      sensor status mask                      .
 *
 * @init
 */
void measurementsStart(mailbox_t *get_mb,uint16_t* sens)
{
  sensors_mb=get_mb;
  tp_measur=chThdCreateStatic(waSensContr, sizeof(waSensContr), NORMALPRIO, sensContr, (void *)sens);
}

/**
 * @brief   Stop polling sensors.                     .
 *
 * @api
 */
void measurementsStop(void)
{
  chThdTerminate(tp_measur);
  chMBPostTimeout(sensors_mb, (msg_t)(-1), TIME_IMMEDIATE);
  chThdWait(tp_measur);
}

