#ifndef INCLUDE_CONTROLLERS_H_
#define INCLUDE_CONTROLLERS_H_
#include "hal.h"
#include "measurements.h"

typedef enum {
  CONTR_UNINIT = 0,      /**< @brief Not initialized.    */
  CONTR_INIT = 1,        /**< @brief Initialization.    */
  CONTR_READY = 2,       /**< @brief Ready.              */
  CONTR_ACTIVE = 3       /**< @brief Active.             */
} contrstate_t;

typedef struct {
  enum{
    NONE_CONTROL = 0,
    PID = 1,
    STH_CONTR = 2
  }type;
  enum{
    NONE_SENS = 0,
    SPEED = 1,
    OTHER = 2
  }sensor;

  struct{
    struct {
     float k_p;
     float k_i;
     float k_d;
    } coef;
  }settingContr;
}controller_t;

typedef struct {
  /**
   * @brief Forces created by P,I,D regulators.
   */
  struct {
    float pr;
    float integ;
    float dif;
  } force;
  /**
   * @brief Errors used by the regulator.
   */
  struct{
    float current;
    float prev;
    float sum;
    float sum_lim;
    float prev_del;
    float current_del;
  }error;
}contrdata_t;


typedef msg_t (*contr_callback_func)(controller_t*,sendata_t*,contrdata_t*);
typedef struct
{
  contr_callback_func contr_initialize;
  contr_callback_func contr_activate;
}contraction_t;

void controllersStart(void);

msg_t pidInit(controller_t*,sendata_t*,contrdata_t*);
msg_t pidAct(controller_t*,sendata_t*,contrdata_t*);


#endif
