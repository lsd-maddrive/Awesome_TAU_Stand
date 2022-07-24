#include "ch.h"
#include "hal.h"
#include <serial.h>
#include "modbusTCP.h"
#include "modbusRegister.h"

// ��� ������ lwip � chibios
#include <lwipthread.h>

// � ��� ��� ��� lwip. ��� ����� ����� ����, �� � ���� ��� �������
#include <lwip/netif.h>
#include <lwip/api.h>

extern uint8_t out_buf[100];


THD_WORKING_AREA(wa_tcp_server, 4096);
THD_FUNCTION(tcp_server, p) {

// ����� ������ ��������
  (void)p;

// ��������� ����������. conn - ���������� ����������, ����� ������ ������� ����
// newconn - ������� ���������� � ��� ��� ����������
  struct netconn *conn, *newconn;
  err_t err;
  struct netbuf* buf;
  uint8_t* data;
  uint16_t len;
  uint16_t answer_len;

// ��������� ���������� � ������ TCP
  conn = netconn_new(NETCONN_TCP);

// ��������� ��������� ��������� ���� �����, ������� ��������� ��� ������. �� ������ ���� ���� �� ��� � � �����
  struct ip4_addr ip;
  IP4_ADDR(&ip, 192, 168, 1, 123);
// ������������ � 80 �����
  netconn_bind(conn, &ip, 80);

// � �������� ��� �������
  netconn_listen(conn);

  while (true)
  {
    palToggleLine(LINE_LED3);
    // ���� ��� ���-�� �����������. ������� �����������
    err = netconn_accept(conn, &newconn);
    // ���� ���-�� ����������� �������� �������
    if (err == ERR_OK)
    {
       while ((err = netconn_recv(newconn, &buf)) == ERR_OK)
       {
         do
         {
           //����� ������ �� �������
           netbuf_data(buf,(void **)&data, &len);
           //������������ ������ ��������� ModbusTCP
           answer_len=modbustcp_go(data);
           //�������� ������ �������
           netconn_write(newconn, out_buf, answer_len, NETCONN_NOCOPY);

         }
         //���� ���������� �� �������
         while (netbuf_next(buf) >= 0);

         netbuf_delete(buf);
       }

       // ����� ���������� ��������� ����������
       netconn_close(newconn);
       netconn_delete(newconn);
     }
  }

}



int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();
    dbgprintf("start\r\n");
    modbus_register_create();
    palToggleLine(LINE_LED1);


// ������ ����� �����
    lwipthread_opts_t opts;
    struct ip4_addr ip, gateway, netmask;
    IP4_ADDR(&ip, 192, 168, 1, 123);
    IP4_ADDR(&gateway, 192, 168, 1, 1);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
// ��������� ����� ����� ���� ��������� �����. ������� ����� � ���� �� ���� ����������
    uint8_t macaddr[6] = {0xC2, 0xAF, 0x51, 0x03, 0xCF, 0x46};

    opts.address = ip.addr;
    opts.gateway = gateway.addr;
    opts.netmask = netmask.addr;
    opts.macaddress = macaddr;
    opts.link_up_cb = NULL;
    opts.link_down_cb = NULL;


// ��������� ������� �������. � ����� ������� �� ������� �������� ��������� � ��� ����� �����������, ���� ������ ����� ����� � ��� �� ����
// ����� �� ���������� ���������, ����������� NULL � �������� ���������. ����� ����� ������������ ��������� �� ��������� �� ����� lwipthread.h
    lwipInit(&opts);
    chThdSleepSeconds(2);

// �������� ����� �������
    chThdCreateStatic(wa_tcp_server, 4096, NORMALPRIO, tcp_server, NULL);

// �������� ���������, ����� �������� ��� �� �������
    while (true) {
        chThdSleepMilliseconds(1000);
        palToggleLine(LINE_LED2);
    }
}
