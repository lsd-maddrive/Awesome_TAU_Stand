#include "ch.h"
#include "hal.h"
#include <terminal_write.h>
#include <chconf.h>

uint16_t arg = 0;

void interapt(void* args){
    args = args;
    palToggleLine(LINE_LED3);
    arg = arg + 1;

}

void test_interaption(void) {
    halInit();
    chSysInit();
    debugStreamInit();


    palSetLineMode(LINE_LED3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, interapt, NULL);

    while (true) {
        chThdSleepMilliseconds(3000);
        dbgPrintf("%d\r\n", arg);
        arg = 0;
    }
}



