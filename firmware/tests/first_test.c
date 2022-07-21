#include <common.h>
#include <tests.h>
#include <terminal_write.h>


void first_test(void) {

    halInit();
    chSysInit();

    debugStreamInit();
    dbgPrintf("Test\n\r");
    uint16_t i = 0;
    while (true) {
        chThdSleepMilliseconds(1000);
        dbgPrintf("%d\n\r", i);
        palToggleLine(LINE_LED2);
        i++;
    }
}
