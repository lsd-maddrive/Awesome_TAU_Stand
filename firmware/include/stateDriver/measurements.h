#ifndef INCLUDE_MEASUREMENTS_H_
#define INCLUDE_MEASUREMENTS_H_
#include "hal.h"

#include<system_setup.h>

#include <current_sensor.h>
#include <absolute_encoder.h>
#include <incremental_encoder.h>


/**
 * @brief   Possible sensor statuses.
 */
typedef enum {
  SEN_NO_ERROR = 0,
  SEN_BUS_ERROR = 1,
  SEN_TIMEOUT =2,
}senstatus_t;


typedef  enum
{
  SEN_OFF = 0,
  SEN_ON = 1
}senstep_t;

typedef msg_t (*callback_function_sensor)(void);

/**
 * @brief Structure of function pointers.
 */
typedef struct
{
  /**
   * @brief The function starts the sensor.
   */
  callback_function_sensor sen_init;
  /**
   * @brief The function of stopping sensors.
   */
  callback_function_sensor sen_uninit;
}senaction_t;


void measurementsStart(mailbox_t *get_mb,uint16_t* sens);
void measurementsStop(void);

#endif
