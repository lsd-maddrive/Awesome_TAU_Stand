#include "lem_lts.h"

// Data of the currnet.
static float zeroCurrent = 0; // To reduce voltage to zero.
static float current = 0; // In amperes.

// To read from ADC.
static uint16_t adc_buf[ADC_BUF_SIZE] = {0};
static float adc_value = 0; // Average value per ADC.

static ADCDriver *adc3 = &ADCD3;

/*
 * @brief	Configuration of the channel.
 *
 * @note	ADC3 is used. Channel 5 is used.
 */
static ADCConversionGroup adcconf3 = {
    .circular = FALSE,
    .num_channels = 1,
    .end_cb = NULL,
    .error_cb = NULL,
    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART,
    .smpr1 = 0,
    .smpr2 = ADC_SMPR2_SMP_AN5(ADC_SAMPLE_144),
    .htr = 0,
    .ltr = 0,
    .sqr1 = 0,
    .sqr2 = 0,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN5)

};

/*
 * @brief	Read data from the ADC.
 *
 * @note	Read data several times for a more accurate measurement.
 *
 * @note	ADC3 is used. Channel 5 is used.
 *
 * @notapi
 */
float lem_adc_read(void){
	adcConvert(adc3, &adcconf3, adc_buf, ADC_BUF_SIZE); // Reads data from the ADC.

	// Count average adc value.
	adc_value = 0;
	for (uint8_t i = 0; i < ADC_BUF_SIZE; i++){
		adc_value += (float) adc_buf[i];
	}
	adc_value = adc_value / ADC_BUF_SIZE;
	return adc_value;
}

/*
 * @brief	Inits ADC to count the current.
 *
 * @note	ADC3 is used. Channel 5 is used.
 *
 * @note	Inits zero position in ADC.
 */
void lemInit(void){
	palSetLineMode(ADC_PIN_LINE, PAL_MODE_INPUT_ANALOG);
	adcStart(adc3, NULL);
	zeroCurrent = lem_adc_read(); // Inits zero position in ADC.
}

/*
 * @brief	Count new current value.
 *
 * @note	Formula can be wrong!
 *
 * @param_out	current		New current value
 */
float lemCurrentRead(void){
	current = (lem_adc_read() - zeroCurrent) * 6 / 625;
	return current;
}

/*
 * @note	Stops ADC.
 *
 * @note	ADC3 is used. Channel 5 is used.
 */
void lemUninit(void){
	adcStop(adc3);
}
