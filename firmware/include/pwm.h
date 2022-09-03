#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#include <common.h>

#define CLOCKWISE_ROTATION          0 // Just for determining the direction of rotation.
#define COUNTERCLOCKWISE_ROTATION   1 // Just for determining the direction of rotation.

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
#define ENGINE_STOP_TIME            500 // The time to wait untill the engine will be stopped completly. In milliseconds.


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
 *      PA7(3) - TIM8_CH1N  \             \   PB0(3) - TIM8_CH2N
 *                           |             |
 *                           |-------------|
 *                           |             |
 *       PC6(3) - TIM8_CH1  \             \   PC7(3) - TIM8_CH2
 *                           |             |
 *                           |             |
 *                           ---------------
 *                                  |
 *                                  | GND
 */
void pwmInitEngine(void);

/*
 *  @brief  Sets voltage and direction of rotation for the engine.
 *
 *  @param[in]  DirectionOfRotation     Direction of rotation of the engine. Can be clockwise and counterclockwise rotation.
 *              Voltage                 Engine voltage. It is setted as a percentage of the maximum voltage value of engine.
 *                                      Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @note   Max voltage value of engine is 24 V.
 *
 *  @note   If you change the direction of rotation you need consider the time to stop the engine. There is no such function.
 *
 *  @note   PWMD8 is used.
 */
void pwmSetEngineParams(uint8_t DirectionOfRotation, uint16_t Voltage);

/*
 *  @brief  Stops the engine completly.
 *
 *  @note   When you stop the engine you need consider the time to stop the engine. There is no such function.
 *
 *  @note   PWMD8 is used.
 */
void pwmStopEngine(void);

/*
 *  @brief  Stops the engine, all used channels and PWM.
 *
 *  @note   You don't need to think about waiting after the engine to stop.
 *
 *  @note   Setting a safe state for used leg.
 *
 *  @note   PWMD8 is used.
 */
void pwmUninitEngine(void);


#endif /* INCLUDE_PWM_H_ */
