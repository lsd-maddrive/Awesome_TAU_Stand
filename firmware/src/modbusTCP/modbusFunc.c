#include "modbusRegister.h"
#include "modbusFunc.h"


extern char out_buf[100];


extern analog_node_t* current_analog;
extern discrete_node_t* current_discrete;

int modbustcp_send_answer_fun_0x04(int tid, int pid, char uid, char func, int counter)
{
  int len=0,len_next=0, len_data, value;
  unsigned char HiByteValue=0, LoByteValue=0,k=0;
  out_buf[MB_TCP_TID]=tid>>8;
  out_buf[MB_TCP_TID+1]=tid;
  out_buf[MB_TCP_PID]=pid>>8;
  out_buf[MB_TCP_PID+1]=pid;
  len_next=counter*2+3;
  out_buf[MB_TCP_LEN]=len_next>>8;
  out_buf[MB_TCP_LEN+1]=len_next;
  out_buf[MB_TCP_UID]=uid;
  out_buf[MB_TCP_FUNC]=func;
  len_data=counter*2;
  out_buf[MB_TCP_FUNC+1]=len_data;
  while(current_analog!=NULL && k<counter)
  {
    value=current_analog->value;
    HiByteValue=value>>8;
    LoByteValue=value;
    out_buf[MB_TCP_Data+k*2]=HiByteValue;
    out_buf[MB_TCP_Data+k*2+1]=LoByteValue;
    current_analog=current_analog->next;
    k++;
  }
  len=counter*2+9; 
  return  len;
}

int modbustcp_send_answer_fun_0x03(int tid, int pid, char uid, char func, int counter)
{
  int len=0,len_next=0, len_data, value;
  unsigned char HiByteValue=0, LoByteValue=0,k=0;
  out_buf[MB_TCP_TID]=tid>>8;
  out_buf[MB_TCP_TID+1]=tid;
  out_buf[MB_TCP_PID]=pid>>8;
  out_buf[MB_TCP_PID+1]=pid;
  len_next=counter*2+3;
  out_buf[MB_TCP_LEN]=len_next>>8;
  out_buf[MB_TCP_LEN+1]=len_next;
  out_buf[MB_TCP_UID]=uid;
  out_buf[MB_TCP_FUNC]=func;
  len_data=counter*2;
  out_buf[MB_TCP_FUNC+1]=len_data;
  while(current_analog!=NULL && k<counter)
  {
    value=current_analog->value;
    HiByteValue=value>>8;
    LoByteValue=value;
    out_buf[MB_TCP_Data+k*2]=HiByteValue;
    out_buf[MB_TCP_Data+k*2+1]=LoByteValue;
    current_analog=current_analog->next;
    k++;
  }
  len=counter*2+9;
  return  len;
}

int modbustcp_send_answer_fun_0x05(int tid, int pid, char uid, char func, int address,char boole)
{
  out_buf[MB_TCP_TID]=tid>>8;
  out_buf[MB_TCP_TID+1]=tid;
  out_buf[MB_TCP_PID]=pid>>8;
  out_buf[MB_TCP_PID+1]=pid;
  out_buf[MB_TCP_LEN]=0x00;
  out_buf[MB_TCP_LEN+1]=0x06;
  out_buf[MB_TCP_UID]=uid;
  out_buf[MB_TCP_FUNC]=func;
  out_buf[MB_TCP_ADDRESS]=address>>8;
  out_buf[MB_TCP_ADDRESS+1]=address;
  if(boole)
  {
    out_buf[MB_TCP_Take_Data]=0xFF;
    out_buf[MB_TCP_Take_Data+1]=0x00;
  }
  else
  {
    out_buf[MB_TCP_Take_Data]=0x00;
    out_buf[MB_TCP_Take_Data+1]=0x00;
  }
  return  12;
}

int modbustcp_send_answer_fun_0x01(int tid, int pid, char uid, char func, int counter)
{
  char len=0,len_next=0, len_data,k=0,i, data=0;
  out_buf[MB_TCP_TID]=tid>>8;
  out_buf[MB_TCP_TID+1]=tid;
  out_buf[MB_TCP_PID]=pid>>8;
  out_buf[MB_TCP_PID+1]=pid;
  if(counter%8)
    len_data=counter/8+1;
  else
    len_data=counter/8;
  len_next=3+len_data;
  out_buf[MB_TCP_LEN]=len_next>>8;
  out_buf[MB_TCP_LEN+1]=len_next;
  out_buf[MB_TCP_UID]=uid;
  out_buf[MB_TCP_FUNC]=func;
  out_buf[MB_TCP_FUNC+1]=len_data;
  while(current_discrete!=NULL && k<len_data)
  {
      i=0;
      while((counter>0) && (i<8))
      {
        data=data+((current_discrete->value)<<i);
        i++;
        counter--;
        current_discrete=current_discrete->next;
      }
      out_buf[MB_TCP_Data+k]=data;
      data=0;
      k++;
  }
  len=9+len_data;
  return  len;
}

int modbustcp_send_answer_fun_0x06(int tid, int pid, char uid, char func, int address,int value)
{
  out_buf[MB_TCP_TID]=tid>>8;
  out_buf[MB_TCP_TID+1]=tid;
  out_buf[MB_TCP_PID]=pid>>8;
  out_buf[MB_TCP_PID+1]=pid;
  out_buf[MB_TCP_LEN]=0x00;
  out_buf[MB_TCP_LEN+1]=0x06;
  out_buf[MB_TCP_UID]=uid;
  out_buf[MB_TCP_FUNC]=func;
  out_buf[MB_TCP_ADDRESS]=address>>8;
  out_buf[MB_TCP_ADDRESS+1]=address;
  out_buf[MB_TCP_Take_Data]=value>>8;
  out_buf[MB_TCP_Take_Data+1]=value;
  return  12;
}
