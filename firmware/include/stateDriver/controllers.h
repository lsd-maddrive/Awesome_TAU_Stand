#ifndef INCLUDE_CONTROLLERS_H_
#define INCLUDE_CONTROLLERS_H_

#include <hal.h>
#include <ch.h>


#include <motor_control.h>
#include <noneControll.h>

typedef enum {
  NONE_CONTROL = 0,
  PID = 1,
  CONTROL2 = 2,
  NUMBER_CONTROL
}contrlist_t;

typedef enum{
  PARAM_SPEED=0,
  PARAM_ANGLE=1,
  PARAM_ROTATE=2,
  PARAM_VOLT=3,
  NUMBER_PARAM
}contrparam_t;

typedef  enum
{
  PARAM_OFF = 0,
  PARAM_ON = 1
}paramstep_t;

typedef struct {
  contrlist_t type;
  uint8_t param;
}controller_t;

typedef msg_t (*callback_function_controll_init)(void*);
typedef msg_t (*callback_function_controll_uninit)(void);
/**
 * @brief Structure of function pointers.
 */
typedef struct
{
  /**
   * @brief The function starts the controller.
   */
  callback_function_controll_init contr_init;
  /**
   * @brief The function of stopping controller.
   */
  callback_function_controll_uninit contr_uninit;
}contraction_t;

void controllersStart(controller_t* set_contr);
void controllersStop(controller_t* set_contr);


#endif
