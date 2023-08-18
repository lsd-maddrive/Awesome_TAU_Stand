#ifndef INCLUDE_LEM_LTS_H_
#define INCLUDE_LEM_LTS_H_

#include "common.h"

#define ADC_BUF_SIZE			5 // To read from the ADC several times.

#define ADC_PIN_LINE			PAL_LINE(GPIOF, 7)


/*
 * @brief	Inits ADC to count the current.
 *
 * @note	ADC3 is used. Channel 5 is used.
 *
 * @note	Inits zero position in ADC.
 */
void lemInit(void);

/*
 * @brief	Count new current value.
 *
 * @note	Formula can be wrong!
 *
 * @param_out	current		New current value
 */
float lemCurrentRead(void);

/*
 * @note	Stops ADC.
 *
 * @note	ADC3 is used. Channel 5 is used.
 */
void lemUninit(void);

#endif /* INCLUDE_LEM_LTS_H_ */
