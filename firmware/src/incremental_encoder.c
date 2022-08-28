#include <incremental_encoder.h>

float IncrementalEncoderRotationalSpeed = 0.0;
uint16_t IncrementalEncoderNumberOfInterrupts = 0;
GPTDriver *timer = &GPTD1;


void incremental_encoder_interrupt_count_velocity(void* args){
    (void)args;
    IncrementalEncoderNumberOfInterrupts = IncrementalEncoderNumberOfInterrupts +1;
}


void incremental_encoder_timer_print_result(GPTDriver *gptp)
{
    (void)gptp;
    IncrementalEncoderRotationalSpeed = IncrementalEncoderNumberOfInterrupts * COEF_INCREMENTAL_ENCODER_VELOCITY;
    dbgPrintf("%.5f\r\n", IncrementalEncoderRotationalSpeed);
    IncrementalEncoderNumberOfInterrupts = 0;
}

GPTConfig incremental_encoder_timer_config = {
    .frequency = TIMER_CONFIG_FREQUENCY,
    .callback = incremental_encoder_timer_print_result,
    .cr2 = 0,
    .dier = 0
};

void incremental_encoder_timer_start(void){
  gptStart(timer, &incremental_encoder_timer_config);
  gptStartContinuous(timer, TIMER_CONFIG_FREQUENCY * TIMER_OUTPUT_PERIOD);
}

void IncrementalEncoderInterruptInit(void){
  incremental_encoder_timer_start();
  palSetPadMode(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, INCREMENTAL_ENCODER_INTERRUPT_PAL_INPUT_MODE);
  palEnablePadEvent(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, INCREMENTAL_ENCODER_INTERRUPT_PAL_EVENT_MODE);
  palSetPadCallback(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, incremental_encoder_interrupt_count_velocity, NULL);
}

void incremental_encoder_timer_stop(void){
  gptStopTimer(timer);
  gptStop(timer);
}

void IncrementalEncoderInterruptUninit(void){
  incremental_encoder_timer_stop();
  palDisablePadEvent(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD);
  palSetPadMode(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, PAL_MODE_UNCONNECTED);
}
