#include <incremental_encoder.h>

float IncrementalEncoderRotationalSpeed = 0.0;
uint16_t IncrementalEncoderNumberOfInterrupts = 0;
GPTDriver *timer = &GPTD1;

/*
 *  @brief  Count ticks from the incremental encoder per period.
 *
 *  @notapi
 */
void incremental_encoder_interrupt_count_ticks(void* args){
    (void)args; // Just to avoid warnings.
    IncrementalEncoderNumberOfInterrupts = IncrementalEncoderNumberOfInterrupts +1;
}

/*
 *  @brief  Count and print incremental encoder velocity.
 *
 *  @note   Print into the terminal encoder speed
 *
 *  @notapi
 */
void incremental_encoder_timer_print_result(GPTDriver *gptp)
{
    (void)gptp; // Just to avoid warnings.
    IncrementalEncoderRotationalSpeed = IncrementalEncoderNumberOfInterrupts * COEF_INCREMENTAL_ENCODER_VELOCITY;
    dbgPrintf("%.5f\r\n", IncrementalEncoderRotationalSpeed);
    IncrementalEncoderNumberOfInterrupts = 0; // Set zero value for new period.
}

/*
 *  @brief Configuration of incremental encoder timer.
 *
 *  @note   frequency   Tick frequency in Hz. Depends on resolution of timer.
 *          callback    A pointer to the interrupt function that will trigger when the timer ends.
 *
 */
GPTConfig incremental_encoder_timer_config = {
    .frequency = TIMER_CONFIG_FREQUENCY,
    .callback = incremental_encoder_timer_print_result,
    .cr2 = 0,
    .dier = 0
};

/*
 *  @brief  Starts timer with needed configuration.
 *
 *  @note   Timer works in continuos mode.
 *
 *  @notapi
 */
void incremental_encoder_timer_start(void){
  gptStart(timer, &incremental_encoder_timer_config);
  gptStartContinuous(timer, TIMER_CONFIG_FREQUENCY * TIMER_OUTPUT_PERIOD);
}

/*
 *  @brief  Starts timer and initialize interrupt.
 *
 *  @note
 */
void IncrementalEncoderInterruptInit(void){
  incremental_encoder_timer_start();
  palSetPadMode(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, INCREMENTAL_ENCODER_INTERRUPT_PAL_INPUT_MODE);
  palEnablePadEvent(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, INCREMENTAL_ENCODER_INTERRUPT_PAL_EVENT_MODE);
  palSetPadCallback(INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT, INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD, incremental_encoder_interrupt_count_tiks, NULL);
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
