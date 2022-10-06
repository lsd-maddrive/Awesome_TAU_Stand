#ifndef INCLUDE_STATEDRIVER_SYSTEM_SETUP_H_
#define INCLUDE_STATEDRIVER_SYSTEM_SETUP_H_


/*===========================================================================*/
/* Types of data related to sensor modules.                                                         */
/*===========================================================================*/
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
 * @brief   Possible loads and related sensors.
 */
typedef enum{
    NONE_LOAD = 0,
    FIRST_LOAD = (1<<SEN_CURRENT) | (1<<SEN_INC_ENCODER)| (1<<SEN_ABS_ENCODER),
    SECOND_LOAD = (1<<SEN_INC_ENCODER) | (1<<SEN_ABS_ENCODER),
    THIRD_LOAD = (1<<SEN_INC_ENCODER)
  }load_t;


/*===========================================================================*/
/* Data types related to motor control modules.                                                         */
/*===========================================================================*/
/**
* @brief   Possible ways to control the motor.
*/
typedef enum {
  MANUAL_CONTROL = 0,
  PID = 1,
  CONTROL2 = 2,
  NUMBER_CONTROL
}contrlist_t;

/**
 * @brief   Possible state variables.
 */
typedef enum{
  PARAM_SPEED=0,
  PARAM_ANGLE=1,
  PARAM_ROTATE=2,
  PARAM_VOLT=3,
  NUMBER_PARAM
}contrstvariable_t;

/**
 * @brief   The structure of the controller configuration.
 */
typedef struct {
  contrlist_t type;
  uint8_t statevariable;
}controller_t;

#endif
