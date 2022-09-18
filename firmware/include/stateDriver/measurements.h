#ifndef INCLUDE_MEASUREMENTS_H_
#define INCLUDE_MEASUREMENTS_H_
#include "hal.h"

#include <current_sensor.h>
#include <absolute_encoder.h>
#include <incremental_encoder.h>

/**
 * @brief   Possible sensors.
 */
typedef enum {
  SEN_CURRENT = 0,
  SEN_ABS_ENCODER = 1,
  SEN_INC_ENCODER = 2,
  NUMBER_SENSORS
}senlist_t;

/**
 * @brief   Possible sensor statuses.
 */
typedef enum {
  SEN_NO_ERROR = 0,
  SEN_BUS_ERROR = 1,
  SEN_TIMEOUT =2,
}senstatus_t;

/**
 * @brief   Possible loads and related sensors.
 */
typedef enum{
    NONE_LOAD = 0,
    FIRST_LOAD = (1<<SEN_CURRENT) | (1<<SEN_INC_ENCODER),
    SECOND_LOAD = (1<<SEN_INC_ENCODER) | (1<<SEN_ABS_ENCODER),
    THIRD_LOAD = (1<<SEN_INC_ENCODER)
  }load_t;

typedef  enum
{
  SEN_OFF = 0,
  SEN_ON = 1
}senstep_t;

typedef void (*callback_function_sensor)(void);

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


void measurementsStart(mailbox_t *get_mb,uint8_t* sens);
void measurementsStop(void);


void senCurrentInit(void);
void senCurrentUninit(void);
void senABSEncoderInit(void);
void senABSEncoderUninit(void);
void senINCEncoderInit(void);
void senINCEncoderUninit(void);

#endif
