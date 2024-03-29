#ifndef INCLUDE_STATE_DRIVER_H_
#define INCLUDE_STATE_DRIVER_H_
#include "hal.h"

#include<system_setup.h>

#include <measurements.h>
#include <controllers.h>
#include <terminal_write.h>

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  STATE_UNINIT = 0,     /**< @brief Not initialized.    */
  STATE_STOP = 1,       /**< @brief Stopped.            */
  STATE_READY = 2,      /**< @brief Ready.              */
  STATE_ACTIVE = 3,     /**< @brief Active.             */
  STATE_ERROR = 4
} dstate_t;

/**
 * @brief   Type of state driver configuration structure.
 */
typedef struct {
  /**
   * @brief   load selection of the connected load.
   * @note    Leave zero if the load is not connected.
   */
  load_t load;
  /**
   * @brief   Sensor status mask.
   */
  uint16_t sens;
  /**
   * @brief   controller selecting the controller settings.
   * @note    Leave zero if the regulator is not used.
   */
  controller_t controller;
}stateConfig_t;


/**
 * @brief   Structure representing an state driver.
 */
typedef struct {
  /**
   * @brief   Current driver state.
   */
  dstate_t state;
  /**
   * @brief   Current configuration data.
   */
  stateConfig_t config;
}stateDriver_t;



msg_t stateDriverInit(stateDriver_t *sdstruct);

msg_t stateDriverStart(stateDriver_t *sdstruct);
msg_t stateDriverStop(stateDriver_t *sdstruct);

msg_t stateDriverActivateMotor(stateDriver_t *sdstruct);
msg_t stateDriverDeactivateMotor(stateDriver_t *sdstruct);

msg_t setNewLoad(stateDriver_t *sdstruct,load_t new_load);
msg_t setNewSen(stateDriver_t *sdstruct,senlist_t sen,senstep_t step);

msg_t setNewControll(stateDriver_t *sdstruct,contrlist_t new_controll);
msg_t setNewParamControll(stateDriver_t *sdstruct,uint8_t new_param_controll,variablestep_t step);

msg_t setNewRequiredSpeed(stateDriver_t *sdstruct,int16_t required_speed);

#endif
