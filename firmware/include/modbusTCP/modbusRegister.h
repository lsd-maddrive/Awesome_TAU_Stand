#ifndef __MODBUSREGISTER_H
#define __MODBUSREGISTER_H

#include "ch.h"
#include "hal.h"


#define REGISTER_LEN 100

extern int16_t Analog_Register[REGISTER_LEN];
extern uint8_t Discrete_Register[REGISTER_LEN];

#define MB_READ_ANALOG_REG(addr)        (*(Analog_register+addr))
#define MB_WRITE_REG_FLOAT(addr,val)    (*(float*)(Analog_Register+addr)=val)
#define MB_WRITE_REG_INT32(addr,val)    (*(int32_t*)(Analog_Register+addr)=val)
#define MB_WRITE_REG_INT16(addr,val)    (*(Analog_register+addr)=val)


#define MB_READ_DISCRET_REG(addr)       (*(Discrete_Register+addr))

//discrete_reg
#define SYSTEM_STOP                     0
#define MEASURE                         1
#define MOTOR                           2

#define FLAG_LOAD_1                     3
#define FLAG_LOAD_2                     4
#define FLAG_LOAD_3                     5

#define FLAG_CONTROLLER_1               6
#define FLAG_CONTROLLER_2               7
#define FLAG_CURRENT                    8
#define FLAG_ABS_ENCODER                9
#define FLAG_INC_ENCODER                10



//analog_reg
#define DATA_SPEED                      0

#define DATA_CURRENT                    1
#define STATUS_CURRENT                  2

#define DATA_INC_ENCODER                3
#define STATUS_INC_ENCODER              5

#define DATA_ABS_ENCODER_ANGLE          6
#define DATA_ABS_ENCODER_ANGLEMULTI     8
#define DATA_ABS_ENCODER_SPEED          10
#define DATA_ABS_ENCODER_ROTATE         12
#define STATUS_ABS_ENCODER              14

#define DATA_CONTR_KP                   15
#define DATA_CONTR_KI                   17
#define DATA_CONTR_KD                   19

#define DATA_CONTR_KP_2                 21
#define DATA_CONTR_KI_2                 23
#define DATA_CONTR_KD_2                 25
#define CONTR_USE_SEN                   27

#define DATA_FORCE_PID                  28
#define DATA_FORCE_KP                   30
#define DATA_FORCE_KI                   32
#define DATA_FORCE_KD                   34


#endif /* MODBUSREGISTER */
