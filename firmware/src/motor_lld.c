#include <motor_lld.h>

// Write a pointer to the timer (with a complementary mode) in a variable.
static PWMDriver *pwm = &PWMD8;

/*
 *  @brief  PWM configuration for the motor.
 *
 *  @note   frequency   Frequency for calculating the generated meander. In Hz.
 *          period      Pperiod for calculating the generated meander. In ticks.
 *          channels    Array of structures, where each structure describes the operation of one channel.
 *          bdtr        This is a dead time which sets the pause between the state change of two complementary legs of the same channel.
 *
 *  @note   Used the first and second channel in complementary mode.
 *
 *  @note   We don't use callbacks, cr2 and dier.
 */
static PWMConfig pwmcfg = {
  .frequency = PWM_CONFIG_FREQUENCY,
  .period = PWM_CONFIG_PERIOD,
  .callback = NULL,
  .channels = {
   // Turn on the first and second channel in complementary mode
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  .cr2 = 0,
  .bdtr = PWM_CONFIG_DEAD_TIME,
  .dier = 0
};

/*
 *  @brief  Sets the operating mode to the selected legs and initializes the PWM.
 *
 *  @note   PWMD8 is used.
 *
 *  @note   For PWMD8 timer and such selected legs: PA7(3) - TIM8_CH1N
 *                                                  PC6(3) - TIM8_CH1
 *                                                  PB0(3) - TIM8_CH2N
 *                                                  PC7(3) - TIM8_CH2
 *
 *          The following diagram for connecting the legs to the driver:
 *
 *                                  | V+
 *                                  |
 *                           ---------------
 *                           |             |
 *                           |             |
 *      PC6(3) - TIM8_CH1   \             \   PC7(3) - TIM8_CH2
 *                           |             |
 *                           |-------------|
 *                           |             |
 *      PA7(3) - TIM8_CH1N  \             \   PB0(3) - TIM8_CH2N
 *                           |             |
 *                           |             |
 *                           ---------------
 *                                  |
 *                                  | GND
 */
void motorSimpleInit(void){
  palSetLineMode(PWM_LINE_CH1N, PWM_MODE_CH1N);
  palSetLineMode(PWM_LINE_CH1, PWM_MODE_CH1);
  palSetLineMode(PWM_LINE_CH2N, PWM_MODE_CH2N);
  palSetLineMode(PWM_LINE_CH2, PWM_MODE_CH2);

  pwmStart(pwm, &pwmcfg);
}

/*
 *  @brief  Sets voltage and direction of rotation for the motor.
 *
 *  @param[in]  DirectionOfRotation     Direction of rotation of the motor. Can be clockwise and counterclockwise rotation.
 *              Voltage                 Motor voltage. It is setted as a percentage of the maximum voltage value of motor.
 *                                      Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @note   Max voltage value of motor is 24 V.
 *
 *  @note   If you change the direction of rotation you need consider the time to stop the engine. There is no such function.
 *
 *  @note   PWMD8 is used.
 */
void motorSetVoltage(int16_t Voltage){
  // Check a percentage of the maximum voltage value.
  if (Voltage > MAX_VOLTAGE_VALUE) Voltage = MAX_VOLTAGE_VALUE;
  else if (Voltage < -MAX_VOLTAGE_VALUE) Voltage = -MAX_VOLTAGE_VALUE;

  // Take into account the direction of rotation.
  if (Voltage >= 0){
    pwmEnableChannel(pwm, PWM_CH1, PWM_PERCENTAGE_TO_WIDTH(pwm, Voltage));
    pwmEnableChannel(pwm, PWM_CH2, PWM_PERCENTAGE_TO_WIDTH(pwm, 0));
  }
  else if (Voltage < 0){
    pwmEnableChannel(pwm, PWM_CH1, PWM_PERCENTAGE_TO_WIDTH(pwm, 0));
    pwmEnableChannel(pwm, PWM_CH2, PWM_PERCENTAGE_TO_WIDTH(pwm, abs(Voltage)));
  }
}

/*
 *  @brief  Stops the motor completly.
 *
 *  @note   When you stop the motor you need consider the time to stop the motor. There is no such function.
 *
 *  @note   PWMD8 is used.
 */
void motorSimpleStop(void){
  pwmDisableChannel(pwm, PWM_CH1);
  pwmDisableChannel(pwm, PWM_CH2);
}

/*
 *  @brief  Stops the motor, all used channels and PWM.
 *
 *  @note   Setting a safe state for used leg.
 *
 *  @note   PWMD8 is used.
 */
void motorSimpleUninit(void){
  motorSimpleStop(); // Stop the motor completly.

  // Stops PWM.
  pwmStop(pwm);

  // Setting a safe state for used leg.
  palSetLineMode(PWM_LINE_CH1N, PAL_MODE_UNCONNECTED);
  palSetLineMode(PWM_LINE_CH1, PAL_MODE_UNCONNECTED);
  palSetLineMode(PWM_LINE_CH2N, PAL_MODE_UNCONNECTED);
  palSetLineMode(PWM_LINE_CH2, PAL_MODE_UNCONNECTED);

}
