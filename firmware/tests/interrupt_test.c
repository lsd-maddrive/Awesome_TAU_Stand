#include "ch.h"
#include "hal.h"
#include <terminal_write.h>
#include <chconf.h>

uint16_t arg = 0;
GPTDriver *timer1 = &GPTD1;

void interrupt(void* args){
    args = args;
    palToggleLine(LINE_LED3);
    arg = arg + 1;

}

GPTConfig gpt1_conf = {
    .frequency = 50000,
    .callback = cbgptfun1,
    .cr2 = 0,
    .dier = 0
};

void cbgptfun1(GPTDriver *gptp)
{
    (void)gptp;
    dbgPrintf("%d", arg);
}

void test_interrupt(void) {
    halInit();
    chSysInit();
    debugStreamInit();

    gptStart(timer1, &gpt1_conf);
    gptStartContinuous(timer1, 1);

    palSetLineMode(LINE_LED3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, interapt, NULL);

    while (true) {
        chThdSleepMilliseconds(1000);
    }
}





