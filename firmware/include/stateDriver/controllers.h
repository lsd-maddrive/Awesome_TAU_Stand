#ifndef INCLUDE_CONTROLLERS_H_
#define INCLUDE_CONTROLLERS_H_

#include <hal.h>
#include <ch.h>

#include<system_setup.h>

#include <motor_control.h>
#include <manualControl.h>


typedef  enum
{
  PARAM_OFF = 0,
  PARAM_ON = 1
}variablestep_t;


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
