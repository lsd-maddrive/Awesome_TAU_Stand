#ifndef INCLUDE_STATE_DRIVER_H_
#define INCLUDE_STATE_DRIVER_H_
#include "hal.h"
#include "measurements.h"
#include "controllers.h"
/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  STATE_UNINIT = 0,   /**< @brief Not initialized.    */
  STATE_STOP = 1,      /**< @brief Stopped.            */
  STATE_READY = 2,    /**< @brief Ready.              */
  STATE_ACTIVE = 3      /**< @brief Active.             */
} dstate_t;


typedef struct {
  load_t load;
  controller_t controller;
}DConfig;

typedef struct {
  dstate_t state;
  const DConfig *config;

}Driver;



msg_t stateDriverInit(Driver *lldp);
msg_t stateDriverStart(Driver *lldp,DConfig *config);
msg_t stateDriverStop(Driver *lldp);
msg_t stateDriverReinit(Driver *lldp,DConfig *config);
msg_t stateDriverActivate(Driver *lldp);
msg_t stateDriverInactivate(Driver *lldp);

#endif
