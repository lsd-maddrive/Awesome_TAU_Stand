#include <tests.h>
#include <terminal_write.h>
#include <scheduler.h>
#include <modbusTCP.h>


#define BUFFER_SIZE 100
mailbox_t main_mb;
msg_t main_mb_buffer[BUFFER_SIZE];

void test_sd(void){
  halInit();
  chSysInit();
  debugStreamInit();

  chMBObjectInit(&main_mb, main_mb_buffer, BUFFER_SIZE);
  schedulerStart();

  modbustcp_init();
  modbustcp_start();

    while (1)
    {
      chThdSleepMilliseconds(1000);
    }
}

