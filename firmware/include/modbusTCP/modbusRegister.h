#ifndef __MODBUSREGISTER_H
#define __MODBUSREGISTER_H

#include "ch.h"
#include "hal.h"


#define REGISTER_LEN 100

extern int16_t Analog_Register[REGISTER_LEN];
extern uint8_t Discrete_Register[REGISTER_LEN];

#define MB_READ_REG_FLOAT(addr)         (*(float*)(Analog_Register+addr))
#define MB_READ_REG_INT32(addr)         (*(int32_t*)(Analog_Register+addr))
#define MB_READ_REG_INT16(addr)         (*(Analog_Register+addr))
#define MB_WRITE_REG_FLOAT(addr,val)    (*(float*)(Analog_Register+addr)=val)
#define MB_WRITE_REG_INT32(addr,val)    (*(int32_t*)(Analog_Register+addr)=val)
#define MB_WRITE_REG_INT16(addr,val)    (*(Analog_Register+addr)=val)


#define MB_READ_DISCRET_REG(addr)       (*(Discrete_Register+addr))
#define MB_WRITE_DISCRET_REG(addr,val)  (*(Discrete_Register+addr)=val)

//discrete_reg
#define SYSTEM_STOP                     0
#define MEASURE                         1
#define MOTOR                           2

#define FLAG_LOAD_1                     3
#define FLAG_LOAD_2                     4
#define FLAG_LOAD_3                     5
#define FLAG_CURRENT                    6
#define FLAG_ABS_ENCODER                7
#define FLAG_INC_ENCODER                8

#define FLAG_CONTROLLER_1               9
#define FLAG_CONTROLLER_2               10
#define FLAG_VARIABLE_SPEED             11
#define FLAG_VARIABLE_ANGLE             12
#define FLAG_VARIABLE_ROTATE            13
#define FLAG_VARIABLE_CURRENT           14

#define STATUS_MOTOR                    15
#define STATUS_CURRENT                  16
#define STATUS_INC_ENCODER              17
#define STATUS_ABS_ENCODER              18


//analog_reg

#define DATA_CURRENT_SENSOR_CURRENT                         0

#define DATA_INC_ENCODER_ROTATIONAL_SPEED                   2

#define DATA_ABS_ENCODER_ANGLE_OF_ROTATION                  4
#define DATA_ABS_ENCODER_MULTI_TURN_ANGLE_OF_ROTATION       6
#define DATA_ABS_ENCODER_ROTATIONAL_SPEED                   8
#define DATA_ABS_ENCODER_NUMBER_OF_TURNS                    10


#define DATA_CONTR_KP                                       12
#define DATA_CONTR_KI                                       14
#define DATA_CONTR_KD                                       16

#define DATA_CONTR_KP_2                                     18
#define DATA_CONTR_KI_2                                     20
#define DATA_CONTR_KD_2                                     22
#define DATA_CONTROL_TIME                                   24

#define DATA_FORCE_PID                                      26
#define DATA_FORCE_KP                                       28
#define DATA_FORCE_KI                                       30
#define DATA_FORCE_KD                                       32

#define DATA_MOTOR_REQUIRED_SPEED                           34
#define DATA_MOTOR_CURRENT_SPEED                            35
#define DATA_MOTOR_REQUIRED_VOLTAGE                         36
#define DATA_MOTOR_CURRENT_VOLTAGE                          37


#endif /* MODBUSREGISTER */
