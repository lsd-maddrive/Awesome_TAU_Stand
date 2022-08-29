#ifndef INCLUDE_INCREMENTAL_ENCODER_H_
#define INCLUDE_INCREMENTAL_ENCODER_H_

#include <common.h>
#include <terminal_write.h>

#define INCREMENTAL_ENCODER_PPR 500
#define GEAR_RATIO 5
/*
 * @brief   This coefficient must be multiplied by the number of interrupts to get the rotation speed in rpm.
 *
 * @note    60/(period of incremental_encoder * maximum number of points in the encoder * gear ratio)
 *
 *          60 - converts to minutes.
 *          period of incremental_encoder - Is seted below in the variable "TIMER_PERIOD_OF_INCREMENTAL_ENCODER" (0.02).
 *          maximum number of points in the encoder - Is seted above in the variable "TIMER_PERIOD_OF_INCREMENTAL_ENCODER" (500).
 *          gear ratio - Is seted above in the variable "GEAR_RATIO" (5).
 *
 */
#define COEF_INCREMENTAL_ENCODER_VELOCITY 60/(TIMER_PERIOD_OF_INCREMENTAL_ENCODER * INCREMENTAL_ENCODER_PPR * GEAR_RATIO)

// Timer configuration.
#define TIMER_CONFIG_FREQUENCY 50000 // This value is set in the timer configuration. In Hz. Affects the resolution of the timer.
#define TIMER_PERIOD_OF_INCREMENTAL_ENCODER 0.02 // Timer operation period. In seconds.

// Interrupts configuration.
#define INCREMENTAL_ENCODER_PORT_A GPIOA // All legs of the same port that will be used for interrupts.
#define INCREMENTAL_ENCODER_PAD_A PAL_LINE(INCREMENTAL_ENCODER_PORT_A, 3) // One leg of the controller that will be used for interrupts.
#define INCREMENTAL_ENCODER_INPUT_MODE_A PAL_MODE_INPUT_PULLDOWN // Line to the entrance with a lift to the ground that interrupts will respond to.

#define INCREMENTAL_ENCODER_PORT_B GPIOC // All legs of the same port that will be used for determining the direction of speed.
#define INCREMENTAL_ENCODER_PAD_B PAL_LINE(INCREMENTAL_ENCODER_PORT_B, 0) // One leg of the controller that will be used for determining the direction of speed.
#define INCREMENTAL_ENCODER_INPUT_MODE_B PAL_MODE_INPUT_PULLDOWN // Line to the entrance with a lift to the ground.


/*
 *  @brief  Starts the timer and initializes interrupts.
 *
 *  @note   GPTD1 is used.
 */
void IncrementalEncoderInterruptInit(void);

/*
 *  @brief  Stops the timer running and interrupts.
 *
 *  @note   GPTD1 is used.
 *
 *  @note   Setting a safe state for used leg.
 */
void IncrementalEncoderInterruptUninit(void);

/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  IncrementalEncoderRotationalSpeed  Encoder rotation speed in rpm.
 */
float getMotorSpeed(void);

#endif /* INCLUDE_INCREMENTAL_ENCODER_H_ */
