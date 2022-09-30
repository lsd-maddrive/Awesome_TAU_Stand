#ifndef INCLUDE_MOTOR_LLD_H_
#define INCLUDE_MOTOR_LLD_H_

#include <common.h>
#include <stdlib.h>


/*
 *  @brief  PWN configuration.
 *
 *  @note   You can use this formula to count period of PWM operation:
 *          PWM_period [s] = period [ticks] / frequency [Hz].
 *
 *  @note   PWM period is 1000 Hz here.
 */
#define PWM_CONFIG_FREQUENCY        1000000 // Frequency for calculating the generated meander. In Hz.
#define PWM_CONFIG_PERIOD           1000 // Period for calculating the generated meander. In ticks.
#define PWM_CONFIG_DEAD_TIME        0b11010110 // Dead time. Dead time is 2 microseconds here.

// Legs which are used to control the engine. PWMD8 is used.
#define PWM_LINE_CH1N               PAL_LINE(GPIOA, 7)
#define PWM_LINE_CH1                PAL_LINE(GPIOC, 6)
#define PWM_LINE_CH2N               PAL_LINE(GPIOB, 0)
#define PWM_LINE_CH2                PAL_LINE(GPIOC, 7)

#define PWM_MODE_CH1N               PAL_MODE_ALTERNATE(3)
#define PWM_MODE_CH1                PAL_MODE_ALTERNATE(3)
#define PWM_MODE_CH2N               PAL_MODE_ALTERNATE(3)
#define PWM_MODE_CH2                PAL_MODE_ALTERNATE(3)

// Channels numbers.
#define PWM_CH1                     0
#define PWM_CH2                     1

#define MAX_VOLTAGE_VALUE           9500 // A percentage of the maximum voltage value that you should not exeed. 9500 is 95%.


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
 *  1.  PC6(3) - TIM8_CH1   \             \   3.  PC7(3) - TIM8_CH2
 *                           |             |
 *                           |-------------|
 *                           |             |
 *  2.  PA7(3) - TIM8_CH1N  \             \   4.  PB0(3) - TIM8_CH2N
 *                           |             |
 *                           |             |
 *                           ---------------
 *                                  |
 *                                  | 5. GND
 */
void motorSimpleInit(void);

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
void motorSetVoltage(int16_t Voltage);

/*
 *  @brief  Stops the motor completly.
 *
 *  @note   When you stop the motor you need consider the time to stop the motor. There is no such function.
 *
 *  @note   PWMD8 is used.
 */
void motorSimpleStop(void);

/*
 *  @brief  Stops the motor, all used channels and PWM.
 *
 *  @note   Setting a safe state for used leg.
 *
 *  @note   PWMD8 is used.
 */
void motorSimpleUninit(void);


#endif /* INCLUDE_MOTOR_LLD_H_ */
