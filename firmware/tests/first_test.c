#include <common.h>
#include <tests.h>
#include "serial.h"
#include "modbusTCP.h"




void first_test(void) {

    halInit();
    chSysInit();

    debug_stream_init();
    dbgprintf("Test\n\r");
    uint16_t i = 0;
    while (true) {
        chThdSleepMilliseconds(1000);
        dbgprintf("%d\n\r", i);
        palToggleLine(LINE_LED2);
        i++;
    }
}


void test_modbustcp (void)
{
  halInit();
  chSysInit();

  modbustcp_init();
  modbustcp_start();

  while (true) {
      chThdSleepMilliseconds(1000);
      palToggleLine(LINE_LED2);
  }
}
