#ifndef __MODBUSFUNC_H
#define __MODBUSFUNC_H

#define MY_ID                    1
#define MB_TCP_TID               0
#define MB_TCP_PID               2
#define MB_TCP_LEN               4
#define MB_TCP_UID               6
#define MB_TCP_FUNC              7
#define MB_TCP_ADDRESS           8
#define MB_TCP_COUNT             10
#define MB_TCP_Data              9
#define MB_TCP_Take_Data         10

int modbustcp_send_answer_fun_0x01(int tid, int pid, char uid, char func, int count);
int modbustcp_send_answer_fun_0x03(int tid, int pid, char uid, char func, int counter);
int modbustcp_send_answer_fun_0x04(int tid, int pid, char uid, char func, int counter);
int modbustcp_send_answer_fun_0x05(int tid, int pid, char uid, char func, int address,char boole);
int modbustcp_send_answer_fun_0x06(int tid, int pid, char uid, char func, int address,int value);



#endif /* MODBUSFUNC */
