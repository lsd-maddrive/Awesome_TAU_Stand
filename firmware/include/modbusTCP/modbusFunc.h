#ifndef __MODBUSFUNC_H
#define __MODBUSFUNC_H

#define MY_ID                           1
#define MB_TCP_TID                      0
#define MB_TCP_PID                      2
#define MB_TCP_LEN                      4
#define MB_TCP_UID                      6
#define MB_TCP_FUNC                     7
#define MB_TCP_ADDRESS                  8
#define MB_TCP_COUNT                    10
#define MB_TCP_COUNT_BYTE               12
#define MB_TCP_MULTIPLE_REGISTER        13
#define MB_TCP_Data                     9
#define MB_TCP_Take_Data                10
#define MB_FUN_READ_ANALOG_INPUT_REGISTER           0x04
#define MB_FUN_READ_ANALOG_OUTPUT_REGISTER          0x03
#define MB_FUN_WRITE_ANALOG_REGISTER                0x06
#define MB_FUN_READ_DISCRETE_OUTPUT_REGISTER        0x01
#define MB_FUN_READ_DISCRETE_INPUT_REGISTER         0x02
#define MB_FUN_WRITE_DISCRETE_REGISTER              0x05
#define MB_FUN_WRITE_MULTIPLE_ANALOG_REGISTER       0x10

int16_t modbusTCP_Read_Analog_Input_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbusTCP_Read_Analog_Output_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbusTCP_Read_Discrete_Output_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbusTCP_Read_Discrete_Input_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbusTCP_Write_Analog_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t value);
int16_t modbusTCP_Write_Discrete_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,uint8_t boole);
int16_t modbusTCP_Write_Multiple_Analog_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t count);

int16_t modbustcp_send_answer_fun_0x01(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbustcp_send_answer_fun_0x03(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address);
int16_t modbustcp_send_answer_fun_0x05(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,uint8_t boole);
int16_t modbustcp_send_answer_fun_0x06(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t value);
int16_t modbustcp_send_answer_fun_0x10(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t count_byte);



#endif /* MODBUSFUNC */
