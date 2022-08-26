#include "ch.h"
#include "hal.h"
#include <terminal_write.h>


float IncrementalEncoderRotationalSpeed = 0.0;
uint16_t IncrementalEncoderNumberOfInterrupts = 0;
GPTDriver *timer = &GPTD1;

#define COEF_INCREMENTAL_ENCODER_VELOCITY 0.5
#define COEF_TIMER_CONFIG_FREQUENCY 50000 // Hz.

void incremental_encoder_interrupt_count_velocity(void* args){
    (void)args;
    IncrementalEncoderRotationalSpeed = IncrementalEncoderNumberOfInterrupts * COEF_INCREMENTAL_ENCODER_VELOCITY;
}


void incremental_encoder_timer_print_result(GPTDriver *gptp)
{
    (void)gptp;
    dbgPrintf("%.5f\r\n", IncrementalEncoderRotationalSpeed);
    IncrementalEncoderNumberOfInterrupts = 0;
}

GPTConfig incremental_encoder_timer_config = {
    .frequency = COEF_TIMER_CONFIG_FREQUENCY,
    .callback = incremental_encoder_timer_print_result,
    .cr2 = 0,
    .dier = 0
};

void incremental_encoder_timer_start(void){
  gptStart(timer, &incremental_encoder_timer_config);
  gptStartContinuous(timer, 50000);
}

void IncrementalEncoderInterruptInit(void){
  incremental_encoder_timer_start();
  palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
  palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
  palSetPadCallback(GPIOC, GPIOC_BUTTON, incremental_encoder_interrupt_count_velocity, NULL);
}

void incremental_encoder_timer_stop(void){
  gptStopTimer(timer);
  gptStop(timer);
}

void IncrementalEncoderInterruptUninit(void){
  incremental_encoder_timer_stop();
  palDisablePadEvent(GPIOC, GPIOC_BUTTON);
  palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_UNCONNECTED);
}

void test_interrupt(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("start\r\n");
    IncrementalEncoderInterruptInit();
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}





