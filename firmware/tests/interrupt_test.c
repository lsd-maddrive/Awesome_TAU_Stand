#include <incremental_encoder.h>
#include <terminal_write.h>

void test_interrupt(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("start\r\n");
    incrementalEncoderInterruptInit();
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}





