
#include "modbusTCP.h"
#include "modbusGet.h"
#include "modbusRegister.h"
#include "modbusFunc.h"


#include <lwipthread.h>

#include <lwip/netif.h>
#include <lwip/api.h>


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

  
uint8_t modbus_out_buf[100];

extern mailbox_t main_mb;


THD_WORKING_AREA(wa_tcp_server, 1024);


THD_FUNCTION(tcp_server, p) {

// To remove the warnings
  (void)p;

// Let's define the variables. conn - internal connection to start listening to the port
// newconn - external connection to the one who knocks
  struct netconn *conn, *newconn;
  err_t err;
  struct netbuf* buf;
  uint8_t* data;
  uint16_t len;
  uint16_t answer_len;

// Starting the connection in TCP mode
  conn = netconn_new(NETCONN_TCP);

  struct ip4_addr ip;
  IP4_ADDR(&ip, 192, 168, 1, 123);
// Connecting to port 80
  netconn_bind(conn, &ip, 80);

// And we start listening to him
  netconn_listen(conn);

  while (true)
  {
    palToggleLine(LINE_LED3);
    // We are waiting for someone to connect. Blocking function
    err = netconn_accept(conn, &newconn);
    // If someone is connected, we start communicating
    if (err == ERR_OK)
    {
       while ((err = netconn_recv(newconn, &buf)) == ERR_OK)
       {
         do
         {
           //Receiving data from the client
           netbuf_data(buf,(void **)&data, &len);
           //Modbus TCP Protocol Response Generation
           answer_len=modbustcp_go(data);
           //Sending a response to the client
           netconn_write(newconn, modbus_out_buf, answer_len, NETCONN_NOCOPY);

         }
         //Until the connection is closed
         while (netbuf_next(buf) >= 0);

         netbuf_delete(buf);
       }

       // After disconnecting, we close the connection
       netconn_close(newconn);
       netconn_delete(newconn);
     }
  }

}

void modbustcp_init(void)
{
  // Setting the STM address
      lwipthread_opts_t opts;
      struct ip4_addr ip, gateway, netmask;
      IP4_ADDR(&ip, 192, 168, 1, 123);
      IP4_ADDR(&gateway, 192, 168, 1, 1);
      IP4_ADDR(&netmask, 255, 255, 255, 0);
  // The mac address seems to be absolutely any. The main thing is that there are no identical ones in the network
      uint8_t macaddr[6] = {0xC2, 0xAF, 0x51, 0x03, 0xCF, 0x46};

      opts.address = ip.addr;
      opts.gateway = gateway.addr;
      opts.netmask = netmask.addr;
      opts.macaddress = macaddr;
      opts.link_up_cb = NULL;
      opts.link_down_cb = NULL;


  // We launch the network driver. From this moment on, the display will start on the connector and the stm will ping if the other end of the cord is in the same network
  // We can not pass the settings by using NULL as an argument. Then the default settings from the lwipthread.h file will be used
      lwipInit(&opts);
      chThdSleepSeconds(2);
}

void modbustcp_start(void)
{
  // Let's start the server flow
  chThdCreateStatic(wa_tcp_server, 1024, NORMALPRIO, tcp_server, NULL);
}

int16_t modbustcp_go(uint8_t* data)
{
  int16_t tid, pid, address, count,len=0;
  uint8_t func, uid;
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
    case MB_FUN_READ_ANALOG_INPUT_REGISTER:
    {
      len=modbusTCP_Read_Analog_Input_Register(tid,pid,uid,func,count,address);
      return len;
    }
    break;
    case MB_FUN_READ_ANALOG_OUTPUT_REGISTER:
    {
      len=modbusTCP_Read_Analog_Output_Register(tid,pid,uid,func,count,address);
      return len;
    }
    break;
    case MB_FUN_WRITE_DISCRETE_REGISTER:
    {
      msg_t perem=(modbustcp_get_boll_value(data)<<16)+(address);
      chMBPostTimeout(&main_mb, perem, TIME_IMMEDIATE);
      len=modbusTCP_Write_Discrete_Register(tid,pid,uid,func,address,Discrete_Register[address]);
      return len;
    }
    break;
    case MB_FUN_READ_DISCRETE_OUTPUT_REGISTER:
    {
      len=modbusTCP_Read_Discrete_Output_Register(tid,pid,uid,func,count,address);
      return len;
    }
    break;
    case MB_FUN_READ_DISCRETE_INPUT_REGISTER:
    {
      len=modbusTCP_Read_Discrete_Input_Register(tid,pid,uid,func,count,address);
      return len;
    }
    break;
    case MB_FUN_WRITE_ANALOG_REGISTER:
    {
      msg_t perem=(modbustcp_get_value(data)<<16)+(address+100);
      chMBPostTimeout(&main_mb, perem, TIME_IMMEDIATE);
      len=modbusTCP_Write_Analog_Register(tid,pid,uid,func, address,Analog_Register[address]);
      return len;
    }
    break;
    case MB_FUN_WRITE_MULTIPLE_ANALOG_REGISTER:
       {
         for(uint8_t perem=0;perem<count;perem++)
         {
           msg_t perm=(modbustcp_get_multiple_register(data,perem)<<16)+(address+100+perem);
           chMBPostTimeout(&main_mb, perm, TIME_IMMEDIATE);
         }
         len=modbusTCP_Write_Multiple_Analog_Register(tid,pid,uid,func, address,count);
         return len;
       }
       break;
       }
    }
  return len; 
}
