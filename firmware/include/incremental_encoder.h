#ifndef INCLUDE_INCREMENTAL_ENCODER_H_
#define INCLUDE_INCREMENTAL_ENCODER_H_

#include <common.h>
#include <terminal_write.h>


#define COEF_INCREMENTAL_ENCODER_VELOCITY 0.5 // This coefficient must be multiplied by the number of interrupts to get the rotation speed.

// Timer configuration.
#define TIMER_CONFIG_FREQUENCY 50000 // Hz. –¿«–≈ÿ¿ﬁŸ¿ﬂ —œŒ—Œ¡ÕŒ—“‹
#define TIMER_PERIOD_OF_INCREMENTAL_ENCODER 1 // seconds

// Interrupts configuration.
#define INCREMENTAL_ENCODER_INTERRUPT_PAL_PORT GPIOC // All legs of the same port that will be used for interrupts.
#define INCREMENTAL_ENCODER_INTERRUPT_PAL_PAD GPIOC_BUTTON // One leg of the controller that will be used for interrupts.
#define INCREMENTAL_ENCODER_INTERRUPT_PAL_INPUT_MODE PAL_MODE_INPUT_PULLDOWN // Line to the entrance with a lift to the ground that interrupts will respond to.
#define INCREMENTAL_ENCODER_INTERRUPT_PAL_EVENT_MODE PAL_EVENT_MODE_RISING_EDGE // Mode of operation for interrupts.

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

#endif /* INCLUDE_INCREMENTAL_ENCODER_H_ */
