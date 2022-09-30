#include <incremental_encoder.h>

float IncrementalEncoderRotationalSpeed = 0.0; // Rotational speed that we calculate from the number of interrupts and coefficient which we ask. In rpm.
int16_t IncrementalEncoderNumberOfInterrupts = 0; // The number of interrupts that we get from the incremental encoder per period.
GPTDriver *timer = &GPTD1; // // Write a pointer to the timer in a variable

/*
 *  @brief  Count number of interrupts from the incremental encoder per period.
 *
 *  @notapi
 */
void incremental_encoder_count(void* args){
    (void)args; // Just to avoid warnings.
    if (palReadLine(INCREMENTAL_ENCODER_PAD_B) == 1) IncrementalEncoderNumberOfInterrupts += 1;
    else IncrementalEncoderNumberOfInterrupts -= 1;
}

/*
 *  @brief  Converts from the number of interrpts per period to the rotational velocity of incremental encoder and print it.
 *
 *  @note   Outputs the encoder velocity to the terminal.
 *
 *  @notapi
 */
void incremental_encoder_speed_calculate(GPTDriver *gptp)
{
    (void)gptp; // Just to avoid warnings.
    IncrementalEncoderRotationalSpeed = IncrementalEncoderNumberOfInterrupts * COEF_INCREMENTAL_ENCODER_VELOCITY;
    MB_WRITE_REG_FLOAT(DATA_INC_ENCODER_ROTATIONAL_SPEED, IncrementalEncoderRotationalSpeed); // Writing data to the modbus
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
    .callback = incremental_encoder_speed_calculate,
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
msg_t incrementalEncoderInterruptInit(void){
  incremental_encoder_timer_start();
  palSetLineMode(INCREMENTAL_ENCODER_PAD_A, INCREMENTAL_ENCODER_INPUT_MODE_A);
  palEnableLineEvent(INCREMENTAL_ENCODER_PAD_A, PAL_EVENT_MODE_RISING_EDGE);
  palSetLineCallback(INCREMENTAL_ENCODER_PAD_A, incremental_encoder_count, NULL);

  palSetLineMode(INCREMENTAL_ENCODER_PAD_B, INCREMENTAL_ENCODER_INPUT_MODE_B);
  return MSG_OK;
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
msg_t incrementalEncoderInterruptUninit(void){
  incremental_encoder_timer_stop();
  palDisablePadEvent(INCREMENTAL_ENCODER_PORT_A, INCREMENTAL_ENCODER_PAD_A);
  palSetLineMode(INCREMENTAL_ENCODER_PAD_A, PAL_MODE_UNCONNECTED);

  palSetLineMode(INCREMENTAL_ENCODER_PAD_B, PAL_MODE_UNCONNECTED);
  return MSG_OK;
}

/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  IncrementalEncoderRotationalSpeed  Encoder rotation speed in rpm.
 */
float getMotorSpeed(void){
  return IncrementalEncoderRotationalSpeed;
}
