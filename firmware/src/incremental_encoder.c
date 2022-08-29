#include <incremental_encoder.h>

float IncrementalEncoderRotationalSpeed = 0.0; // Rotational speed that we calculate from the number of interrupts and coefficient which we ask.
int16_t IncrementalEncoderNumberOfInterrupts = 0; // The number of interrupts that we get from the incremental encoder per period.
GPTDriver *timer = &GPTD1; // // Write a pointer to the timer in a variable

/*
 *  @brief  Count number of interrupts from the incremental encoder per period.
 *
 *  @notapi
 */
void incremental_encoder_interrupt_count_interrupts(void* args){
    (void)args; // Just to avoid warnings.
    if (palReadPad(INCREMENTAL_ENCODER_PORT_B, INCREMENTAL_ENCODER_PAD_B) == 1) IncrementalEncoderNumberOfInterrupts += 1;
    else IncrementalEncoderNumberOfInterrupts -= 1;
}

/*
 *  @brief  Converts from the number of interrpts per period to the rotational velocity of incremental encoder and print it.
 *
 *  @note   Outputs the encoder velocity to the terminal.
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
 *  @note   frequency   Tick frequency in Hz. Affects the resolution of the timer.
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
 *  @brief  Starts the timer with selected configuration and period of operation.
 *
 *  @note   Timer works in continuos mode.
 *
 *  @note   GPTD1 is used.
 *
 *  @notapi
 */
void incremental_encoder_timer_start(void){
  gptStart(timer, &incremental_encoder_timer_config);
  gptStartContinuous(timer, TIMER_CONFIG_FREQUENCY * TIMER_PERIOD_OF_INCREMENTAL_ENCODER);
}

/*
 *  @brief  Starts the timer and initializes interrupts.
 *
 *  @note   GPTD1 is used.
 */
void IncrementalEncoderInterruptInit(void){
  incremental_encoder_timer_start();
  palSetPadMode(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A, INCREMENTAL_ENCODER_INPUT_MODE_A);
  palEnablePadEvent(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A, PAL_EVENT_MODE_RISING_EDGE);
  palSetPadCallback(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A, incremental_encoder_interrupt_count_interrupts, NULL);

  palSetPadMode(INCREMENTAL_ENCODER_PORT_B, INCREMENTAL_ENCODER_PAD_B, INCREMENTAL_ENCODER_INPUT_MODE_B);
}

/*
 *  @brief  Stops the timer running in continuous operation.
 *
 *  @note   GPTD1 is used.
 *
 *  @notapi
 */
void incremental_encoder_timer_stop(void){
  gptStopTimer(timer);
  gptStop(timer);
}

/*
 *  @brief  Stops the timer running and interrupts.
 *
 *  @note   GPTD1 is used.
 *
 *  @note   Setting a safe state for used leg.
 */
void IncrementalEncoderInterruptUninit(void){
  incremental_encoder_timer_stop();
  palDisablePadEvent(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A);
  palSetPadMode(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A, PAL_MODE_UNCONNECTED);

  palSetPadMode(INCREMENTAL_ENCODER_PORT_B, INCREMENTAL_ENCODER_PAD_B, PAL_MODE_UNCONNECTED);
}
