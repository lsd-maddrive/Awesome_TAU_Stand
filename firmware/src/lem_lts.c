#include "lem_lts.h"

static float zeroCurrent = 0;
static float current = 0;

static uint16_t adc_buf[5] = {0};
static float adc_value = 0;


static ADCConversionGroup adcconf3 = {
    // Непрерывный режим не нужен
    .circular = FALSE,
    // Канал всего один
    .num_channels = 1,
    // Callback функции не нужны
    .end_cb = NULL,
    .error_cb = NULL,
    // Здесь можно поменять разрешение (номинально 12 бит) и включить watchdog (сейчас выключен)
    .cr1 = 0,
    // Пусть Chibi сама разбирается, как запускать преобразование
    .cr2 = ADC_CR2_SWSTART,
    // Выбираем для третьего канала АЦП самый быстрый режим работы, 3 такта на одно преобразование
    .smpr1 = 0,
    .smpr2 = ADC_SMPR2_SMP_AN5(ADC_SAMPLE_144),
    // Watchdog выключен, значит и пределы никого не интересуют
    .htr = 0,
    .ltr = 0,
    // Так как канал только один, значит указываем только в первом элементе последовательности желаемый канал
    .sqr1 = 0,
    .sqr2 = 0,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN5)

};

float lem_adc_read(void){
	adcConvert(&ADCD3, &adcconf3, adc_buf, 5);
	for (uint8_t i = 0; i < 5; i++){
		adc_value += (float) adc_buf[i];
	}
	adc_value = adc_value / 5;
	return adc_value;
}

void lemInit(void){
	palSetLineMode(PAL_LINE(GPIOF, 7), PAL_MODE_INPUT_ANALOG);
	adcStart(&ADCD3, NULL);

	zeroCurrent = lem_adc_read();
}

float lemCurrentRead(void){
	current = ((lem_adc_read() - zeroCurrent) * 6) / 0.625;
	return current;
}

void lemUninit(void){
	adcStop(&ADCD3);
}
