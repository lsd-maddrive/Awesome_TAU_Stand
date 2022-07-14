#include <common.h>
#include <tests.h>
#include <terminal_write.h>


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
