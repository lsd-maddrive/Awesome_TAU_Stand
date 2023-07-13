#ifndef INCLUDE_CONTROLLFUNC_SLAVECONTROL_H_
#define INCLUDE_CONTROLLFUNC_SLAVECONTROL_H_
#include "hal.h"

#include<system_setup.h>
#include <modbusRegister.h>


/**
* @brief   Conversion of the user speed in the range -24..+24 to -1160..1160.
*/
#define VOLTAGE_TO_INC_ENCODER_ROTATE(speed) (speed*48)

/**
* @brief Errors used by the PID regulator.
*/
typedef struct{
      float current;
      float prev;
      float sum;
      float sum_lim;
      float prev_del;
      float current_del;
    }piderror_t;

typedef struct {
        float pr;
        float integ;
        float dif;
      }pidforce_t;

/**
 * @brief Parameters of the PID controller.
 */
typedef struct {
    pidforce_t force_speed;
    piderror_t error_speed;
    /**
     * @brief Final force of the regulator.
     */
    float sum_force;
} pid_t;

msg_t slaveControlInit(void* stateVariable);
msg_t slaveControlUninit(void);


#endif
