#include "ch.h"
#include "hal.h"
#include <serial.h>
#include "modbusTCP.h"
#include "modbusRegister.h"

// Это связка lwip с chibios
#include <lwipthread.h>

// А это уже сам lwip. Там много всего есть, но я мало что понимаю
#include <lwip/netif.h>
#include <lwip/api.h>

extern uint8_t out_buf[100];


THD_WORKING_AREA(wa_tcp_server, 4096);
THD_FUNCTION(tcp_server, p) {

// Чтобы убрать ворнинги
  (void)p;

// Определим переменные. conn - внутреннее соединение, чтобы начать слушать порт
// newconn - внешнее соединение с тем кто постучится
  struct netconn *conn, *newconn;
  err_t err;
  struct netbuf* buf;
  uint8_t* data;
  uint16_t len;
  uint16_t answer_len;

// Запускаем соединение в режиме TCP
  conn = netconn_new(NETCONN_TCP);

// Поленился нормально прокинуть сюда адрес, поэтому определяю его заново. Он должен быть такй же как и в мейне
  struct ip4_addr ip;
  IP4_ADDR(&ip, 192, 168, 1, 123);
// Подключаемся к 80 порту
  netconn_bind(conn, &ip, 80);

// И начинаем его слушать
  netconn_listen(conn);

  while (true)
  {
    palToggleLine(LINE_LED3);
    // Ждем что кто-то подключится. Функция блокирующая
    err = netconn_accept(conn, &newconn);
    // Если кто-то подключился начинаем общение
    if (err == ERR_OK)
    {
       while ((err = netconn_recv(newconn, &buf)) == ERR_OK)
       {
         do
         {
           //Прием данных от клиента
           netbuf_data(buf,(void **)&data, &len);
           //Формирование ответа протокола ModbusTCP
           answer_len=modbustcp_go(data);
           //Отправка ответа клиенту
           netconn_write(newconn, out_buf, answer_len, NETCONN_NOCOPY);

         }
         //Пока соединение не закрыто
         while (netbuf_next(buf) >= 0);

         netbuf_delete(buf);
       }

       // После отключения закрываем соединение
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


// Задаем адрес стмки
    lwipthread_opts_t opts;
    struct ip4_addr ip, gateway, netmask;
    IP4_ADDR(&ip, 192, 168, 1, 123);
    IP4_ADDR(&gateway, 192, 168, 1, 1);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
// Макадресс вроде может быть абсолютно любой. Главное чтобы в сети не было одинаковых
    uint8_t macaddr[6] = {0xC2, 0xAF, 0x51, 0x03, 0xCF, 0x46};

    opts.address = ip.addr;
    opts.gateway = gateway.addr;
    opts.netmask = netmask.addr;
    opts.macaddress = macaddr;
    opts.link_up_cb = NULL;
    opts.link_down_cb = NULL;


// Запускаем сетевой драйвер. С этого момента на разьеме начнется индикация и стм будет пинговаться, если другой конец шнура в той же сети
// Можем не передавать настройки, использовав NULL в качестве аргумента. Тогда будут использованы настройки по умолчанию из файла lwipthread.h
    lwipInit(&opts);
    chThdSleepSeconds(2);

// Запустим поток сервера
    chThdCreateStatic(wa_tcp_server, 4096, NORMALPRIO, tcp_server, NULL);

// Помигаем лампочкой, чтобы понимать что не зависли
    while (true) {
        chThdSleepMilliseconds(1000);
        palToggleLine(LINE_LED2);
    }
}
