#include "lem_lts.h"

static float zeroCurrent = 0;
static float current = 0;

static uint16_t adc_buf[5] = {0};
static float adc_value = 0;


static ADCConversionGroup adcconf3 = {
    // ����������� ����� �� �����
    .circular = FALSE,
    // ����� ����� ����
    .num_channels = 1,
    // Callback ������� �� �����
    .end_cb = NULL,
    .error_cb = NULL,
    // ����� ����� �������� ���������� (���������� 12 ���) � �������� watchdog (������ ��������)
    .cr1 = 0,
    // ����� Chibi ���� �����������, ��� ��������� ��������������
    .cr2 = ADC_CR2_SWSTART,
    // �������� ��� �������� ������ ��� ����� ������� ����� ������, 3 ����� �� ���� ��������������
    .smpr1 = 0,
    .smpr2 = ADC_SMPR2_SMP_AN5(ADC_SAMPLE_144),
    // Watchdog ��������, ������ � ������� ������ �� ����������
    .htr = 0,
    .ltr = 0,
    // ��� ��� ����� ������ ����, ������ ��������� ������ � ������ �������� ������������������ �������� �����
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
