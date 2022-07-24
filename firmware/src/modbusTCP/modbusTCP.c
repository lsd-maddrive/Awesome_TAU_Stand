#include "ch.h"
#include "hal.h"
#include "modbusTCP.h"
#include "modbusGet.h"
#include "modbusRegister.h"
#include "modbusFunc.h"
#include <serial.h>
#include "string.h"


/* ----------------------- MBAP Header --------------------------------------*/
/*
 *
 * <------------------------ MODBUS TCP/IP ADU(1) ------------------------->
 *              <----------- MODBUS PDU (1') ---------------->
 *  +-----------+---------------+------------------------------------------+
 *  | TID | PID | Length | UID  |Code | Data                               |
 *  +-----------+---------------+------------------------------------------+
 *  |     |     |        |      |
 * (2)   (3)   (4)      (5)    (6)
 *
 * (2)  ... MB_TCP_TID          = 0 (Transaction Identifier - 2 Byte)
 * (3)  ... MB_TCP_PID          = 2 (Protocol Identifier - 2 Byte)
 * (4)  ... MB_TCP_LEN          = 4 (Number of bytes - 2 Byte)
 * (5)  ... MB_TCP_UID          = 6 (Unit Identifier - 1 Byte)
 * (6)  ... MB_TCP_FUNC         = 7 (Modbus Function Code)
 *
 * (1)  ... Modbus TCP/IP Application Data Unit
 * (1') ... Modbus Protocol Data Unit
 */

  
uint8_t out_buf[100];

extern analog_node_t* current_analog;
extern discrete_node_t* current_discrete;
extern analog_node_t* Reg_analog_1;
extern discrete_node_t* Reg_discrete_1;



int modbustcp_go(uint8_t* data)
{
  int tid, pid, address, count,len=0,value;
  char func, uid;
  current_analog=Reg_analog_1;
  current_discrete=Reg_discrete_1;
  tid=modbustcp_get_tid(data);
  pid=modbustcp_get_pid(data);
  uid=modbustcp_get_uid(data);
  func=modbustcp_get_func(data);
  address=modbustcp_get_address(data);
  count=modbustcp_get_count(data);
  if(uid==MY_ID)
  {
    switch(func)
    {
    case 0x04:
    {
      while(current_analog!=NULL)
      {
        if(current_analog->address==address)
        {
          palToggleLine(LINE_LED1);
          len=modbustcp_send_answer_fun_0x04(tid,pid,uid,func,count);
          return len; 
        }
        else
        {
          current_analog=current_analog->next;
        }
      }
    }
    break;
    case 0x03:
    {
      while(current_analog!=NULL)
      {
        if(current_analog->address==address)
        {
          len=modbustcp_send_answer_fun_0x03(tid,pid,uid,func,count);
          return len; 
        }
        else 
          current_analog=current_analog->next;
      }
    }
    break;
    case 0x05:
    {
      while(current_discrete!=NULL)
      {
        if(current_discrete->address==address)
        {
          current_discrete->value=modbustcp_get_boll_value(data);
          len=modbustcp_send_answer_fun_0x05(tid,pid,uid,func,address,current_discrete->value);
          return len; 
        }
        else 
          current_discrete=current_discrete->next;
      }
    }
    break;
    case 0x01:
    {
      while(current_discrete!=NULL)
      {
        if(current_discrete->address==address)
        {
          len=modbustcp_send_answer_fun_0x01(tid,pid,uid,func,count);
          return len; 
        }
        else 
          current_discrete=current_discrete->next;
      }
    }
    break;
    case 0x06:
    {
      while(current_analog!=NULL)
      { 
        if(current_analog->address==address)
        {
          value=modbustcp_get_value(data);
          current_analog->value=value;
          len=modbustcp_send_answer_fun_0x06(tid,pid,uid,func, address,value);
          return len; 
        }
        else 
          current_analog=current_analog->next;
      }
    }
    break;
    }
  } 
  return len; 
}



