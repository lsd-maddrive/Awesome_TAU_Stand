#include <common.h>
#include <tests.h>
#include <terminal_write.h>
#include "modbusTCP.h"
#include "scheduler_state_driver.h"


#define BUFFER_SIZE 100
mailbox_t main_mb;
msg_t main_mb_buffer[BUFFER_SIZE];

void sd_test(void){
  halInit();
  chSysInit();
  debugStreamInit();

  chMBObjectInit(&main_mb, main_mb_buffer, BUFFER_SIZE);
  disStateDriverStart();

  modbustcp_init();
  modbustcp_start();

    while (1)
    {
      chThdSleepMilliseconds(1000);
    }
}

