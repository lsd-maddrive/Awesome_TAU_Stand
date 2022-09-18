#ifndef INCLUDE_STATE_DRIVER_H_
#define INCLUDE_STATE_DRIVER_H_
#include "hal.h"
#include "measurements.h"
#include <terminal_write.h>

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  STATE_UNINIT = 0,     /**< @brief Not initialized.    */
  STATE_STOP = 1,       /**< @brief Stopped.            */
  STATE_READY = 2,      /**< @brief Ready.              */
  STATE_ACTIVE = 3      /**< @brief Active.             */
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
  uint8_t sens;
  /**
   * @brief   controller selecting the controller settings.
   * @note    Leave zero if the regulator is not used.
   */
//  controller_t controller;
}sdConfig_t;


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
  sdConfig_t config;
}sdDriver_t;



msg_t stateDriverInit(sdDriver_t *sdstruct);
msg_t stateDriverStart(sdDriver_t *sdstruct);
msg_t stateDriverStop(sdDriver_t *sdstruct);

msg_t stateDriverActivateMotor(sdDriver_t *sdstruct);
msg_t stateDriverDeactivateMotor(sdDriver_t *sdstruct);

msg_t setNewLoad(sdDriver_t *sdstruct,load_t new_load);
msg_t setNewSen(sdDriver_t *sdstruct,senlist_t sen,senstep_t step);
#endif
