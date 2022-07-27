#ifndef INCLUDE_MEASUREMENTS_H_
#define INCLUDE_MEASUREMENTS_H_
#include "hal.h"

/**
 * @brief   Driver of possible sensor states.
 */
typedef enum {
  SEN_UNINIT = 0,    /**< @brief Not initialized.    */
  SEN_INIT = 1,      /**< @brief Initialization.    */
  SEN_READY = 2,     /**< @brief Ready.              */
  SEN_ACTIVE = 3     /**< @brief Active.             */
} senstate_t;

/**
 * @brief   Driver of possible sensor states.
 */
typedef enum{
    NONE_LOAD = 0,
    FIRST_LOAD = 1,
    SECOND_LOAD = 2,
    THIRD_LOAD = 3
  }load_t;

enum senlist {
  SEN_CURRENT = 0,
  SEN_ENCODER = 1,
};

typedef struct {
  enum
  {
    SEN_OFF = 0,
    SEN_ON = 1
  }sen_status;
  enum
  {
    NO_ERROR = 0,
    SOME_ERROR = 1
  }sen_error;
  struct
  {
    float prev;
    float current;
  }measur;
}sendata_t;

typedef msg_t (*callback_function)(sendata_t*);
typedef struct
{
  callback_function sen_initialize;
  callback_function sen_activate;
}senaction_t;


void measurementsStart(void);
void setNewLoad(load_t new_load);

void getSensorsData(sendata_t* sendata);


msg_t noneLoadInit(sendata_t*);
msg_t noneLoadAct(sendata_t*);
msg_t firstLoadInit(sendata_t*);
msg_t firstLoadAct(sendata_t*);
msg_t secondLoadInit(sendata_t*);
msg_t secondLoadAct(sendata_t*);
msg_t thirdLoadInit(sendata_t*);
msg_t thirdLoadAct(sendata_t*);
#endif
