#include "ch.h"
#include "hal.h"
#include "modbusFunc.h"
#include "modbusGet.h"

extern char in_buf[100];

//The Function returns the Transaction ID
int modbustcp_get_tid(uint8_t* data)
{
  int tid = data[MB_TCP_TID] << 8U;
  tid |= data[MB_TCP_TID + 1];
  return tid;
}

//The Function returns the Protocol ID
int modbustcp_get_pid(uint8_t* data)
{
  int pid = data[MB_TCP_PID] << 8U;
  pid |= data[MB_TCP_PID + 1];
  return pid;
}
//The Function returns the Length
int modbustcp_get_len(uint8_t* data)
{
  int len = data[MB_TCP_LEN] << 8U;
  len |= data[MB_TCP_LEN + 1]+6;
  return len;
}
//The Function returns the Device address
char modbustcp_get_uid(uint8_t* data)
{
  char uid = data[MB_TCP_UID];
  return uid;
}
//The Function returns the Functional code
char modbustcp_get_func(uint8_t* data)
{
  char func = data[MB_TCP_FUNC];
  return func;
}
//The Function returns the Register Address
int modbustcp_get_address(uint8_t* data)
{
  int address = data[MB_TCP_ADDRESS] << 8U;
  address |= data[MB_TCP_ADDRESS + 1];
  return address;
}
//The Function returns the Number of Registers
int modbustcp_get_count(uint8_t* data)
{
  int count = data[MB_TCP_COUNT] << 8U;
  count |= data[MB_TCP_COUNT + 1];
  return count;
}

//The Function returns 
char modbustcp_get_boll_value(uint8_t* data)
{
  unsigned char boll = data[MB_TCP_Take_Data];
  if(boll)
    return 1;
  else
    return 0;
}

//The Function returns Value
int modbustcp_get_value(uint8_t* data)
{
  int value = data[MB_TCP_Take_Data] << 8U;
  value |= data[MB_TCP_Take_Data + 1];
  return value;
}
