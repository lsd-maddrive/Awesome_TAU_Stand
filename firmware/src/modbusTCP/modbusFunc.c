#include "modbusRegister.h"
#include "modbusFunc.h"
#include <hal.h>
#include <ch.h>

extern uint8_t modbus_out_buf[100];



//Forming a response to reading the input analog register. Modbus TCP function-0x04.
int16_t modbusTCP_Read_Analog_Input_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter,int16_t address)
{
	return modbustcp_send_answer_fun_0x03( tid, pid, uid, func, counter, address);
}

//Forming a response to reading the output analog register. Modbus TCP function-0x03.
int16_t modbusTCP_Read_Analog_Output_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address)
{
	return modbustcp_send_answer_fun_0x03( tid, pid, uid, func, counter, address);
}

//Forming a response to reading a discrete output register. Modbus TCP function-0x01.
int16_t modbusTCP_Read_Discrete_Output_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter,int16_t address)
{
	return modbustcp_send_answer_fun_0x01( tid, pid, uid, func, counter, address);
}

//Forming a response to reading a discrete input register. Modbus TCP function-0x01.
int16_t modbusTCP_Read_Discrete_Input_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter,int16_t address)
{
    return modbustcp_send_answer_fun_0x01( tid, pid, uid, func, counter, address);
}

//Formation of the response to the recording of the analog register. Modbus TCP function-0x06.
int16_t modbusTCP_Write_Analog_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t value)
{
	return modbustcp_send_answer_fun_0x06( tid, pid, uid, func, address, value);
}

//Formation of the response to the recording of the multiple analog register. Modbus TCP function-0x10.
int16_t modbusTCP_Write_Multiple_Analog_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t count)
{
    return modbustcp_send_answer_fun_0x10(tid, pid, uid, func, address, count);
}

//Formation of a response to the recording of a discrete register. Modbus TCP function-0x05.
int16_t modbusTCP_Write_Discrete_Register(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,uint8_t boole)
{
	return modbustcp_send_answer_fun_0x05(tid, pid, uid,  func, address, boole);
}



int16_t modbustcp_send_answer_fun_0x03(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter,int16_t address)
{
  int16_t len=0,len_next=0, len_data, value;
  uint8_t HiByteValue=0, LoByteValue=0,k=0;
  modbus_out_buf[MB_TCP_TID]=tid>>8;
  modbus_out_buf[MB_TCP_TID+1]=tid;
  modbus_out_buf[MB_TCP_PID]=pid>>8;
  modbus_out_buf[MB_TCP_PID+1]=pid;
  len_next=counter*2+3;
  modbus_out_buf[MB_TCP_LEN]=len_next>>8;
  modbus_out_buf[MB_TCP_LEN+1]=len_next;
  modbus_out_buf[MB_TCP_UID]=uid;
  modbus_out_buf[MB_TCP_FUNC]=func;
  len_data=counter*2;
  modbus_out_buf[MB_TCP_FUNC+1]=len_data;
  while((address+k)<REGISTER_LEN && k<counter)
  {
    value=Analog_Register[address+k];
    HiByteValue=value>>8;
    LoByteValue=value;
    modbus_out_buf[MB_TCP_Data+k*2]=HiByteValue;
    modbus_out_buf[MB_TCP_Data+k*2+1]=LoByteValue;
    k++;
  }
  len=counter*2+9;
  return  len;
}

int16_t modbustcp_send_answer_fun_0x05(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,uint8_t boole)
{
  modbus_out_buf[MB_TCP_TID]=tid>>8;
  modbus_out_buf[MB_TCP_TID+1]=tid;
  modbus_out_buf[MB_TCP_PID]=pid>>8;
  modbus_out_buf[MB_TCP_PID+1]=pid;
  modbus_out_buf[MB_TCP_LEN]=0x00;
  modbus_out_buf[MB_TCP_LEN+1]=0x06;
  modbus_out_buf[MB_TCP_UID]=uid;
  modbus_out_buf[MB_TCP_FUNC]=func;
  modbus_out_buf[MB_TCP_ADDRESS]=address>>8;
  modbus_out_buf[MB_TCP_ADDRESS+1]=address;
  if(boole)
  {
    modbus_out_buf[MB_TCP_Take_Data]=0xFF;
    modbus_out_buf[MB_TCP_Take_Data+1]=0x00;
  }
  else
  {
    modbus_out_buf[MB_TCP_Take_Data]=0x00;
    modbus_out_buf[MB_TCP_Take_Data+1]=0x00;
  }
  return  12;
}

int16_t modbustcp_send_answer_fun_0x01(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t counter, int16_t address)
{
  uint8_t len=0,len_next=0, len_data,k=0,i, data=0, j=0;
  modbus_out_buf[MB_TCP_TID]=tid>>8;
  modbus_out_buf[MB_TCP_TID+1]=tid;
  modbus_out_buf[MB_TCP_PID]=pid>>8;
  modbus_out_buf[MB_TCP_PID+1]=pid;
  if(counter%8)
    len_data=counter/8+1;
  else
    len_data=counter/8;
  len_next=3+len_data;
  modbus_out_buf[MB_TCP_LEN]=len_next>>8;
  modbus_out_buf[MB_TCP_LEN+1]=len_next;
  modbus_out_buf[MB_TCP_UID]=uid;
  modbus_out_buf[MB_TCP_FUNC]=func;
  modbus_out_buf[MB_TCP_FUNC+1]=len_data;
  while((address+k)<REGISTER_LEN && k<len_data)
  {
      i=0;
      while((counter>0) && (i<8))
      {
        data=data+((Discrete_Register[address+j])<<i);
        i++;
        counter--;
        j++;
      }
      modbus_out_buf[MB_TCP_Data+k]=data;
      data=0;
      k++;
  }
  len=9+len_data;
  return  len;
}

int16_t modbustcp_send_answer_fun_0x06(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t value)
{
  modbus_out_buf[MB_TCP_TID]=tid>>8;
  modbus_out_buf[MB_TCP_TID+1]=tid;
  modbus_out_buf[MB_TCP_PID]=pid>>8;
  modbus_out_buf[MB_TCP_PID+1]=pid;
  modbus_out_buf[MB_TCP_LEN]=0x00;
  modbus_out_buf[MB_TCP_LEN+1]=0x06;
  modbus_out_buf[MB_TCP_UID]=uid;
  modbus_out_buf[MB_TCP_FUNC]=func;
  modbus_out_buf[MB_TCP_ADDRESS]=address>>8;
  modbus_out_buf[MB_TCP_ADDRESS+1]=address;
  modbus_out_buf[MB_TCP_Take_Data]=value>>8;
  modbus_out_buf[MB_TCP_Take_Data+1]=value;
  return  12;
}

int16_t modbustcp_send_answer_fun_0x10(int16_t tid, int16_t pid, uint8_t uid, uint8_t func, int16_t address,int16_t count)
{
  modbus_out_buf[MB_TCP_TID]=tid>>8;
  modbus_out_buf[MB_TCP_TID+1]=tid;
  modbus_out_buf[MB_TCP_PID]=pid>>8;
  modbus_out_buf[MB_TCP_PID+1]=pid;
  modbus_out_buf[MB_TCP_LEN]=0x00;
  modbus_out_buf[MB_TCP_LEN+1]=0x06;
  modbus_out_buf[MB_TCP_UID]=uid;
  modbus_out_buf[MB_TCP_FUNC]=func;
  modbus_out_buf[MB_TCP_ADDRESS]=address>>8;
  modbus_out_buf[MB_TCP_ADDRESS+1]=address;
  modbus_out_buf[MB_TCP_Take_Data]=count>>8;
  modbus_out_buf[MB_TCP_Take_Data+1]=count;
  return  12;
}
