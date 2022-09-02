#include <pwm.h>


//uint8_t DirectionOfRotation = CLOCKWISE_ROTATION;
//uint8_t Voltage = 70; // 0....100

// Структура конфигурации
static PWMConfig pwmcfg = {
  // Частота 10кГц
  .frequency = 100000,
  // Период 5000 тактов, или 0,05с
  .period = 5000,
  // Ссылка на функцию
  .callback = NULL,
  .channels = {
   // Включаем первый канал в комплементарном режиме, с вызовом второй функции
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  .cr2 = 0,
  // Задаем мёртвое время 2мкс
  .bdtr = 0b11010110,
  .dier = 0
};
// Сохраняем указатель на первый драйвер в переменную
static PWMDriver *pwm = &PWMD8;

void pwmInit(void){
  pwmStart(pwm, &pwmcfg);
  palSetLineMode(PAL_LINE(GPIOC, 6), PAL_MODE_ALTERNATE(3));
  palSetLineMode(PAL_LINE(GPIOA, 7), PAL_MODE_ALTERNATE(3));
}

void pwmCheakingDirectionAndVoltage(uint8_t DirectionOfRotation, uint8_t Voltage){
  if (DirectionOfRotation == CLOCKWISE_ROTATION){
    pwmEnableChannel(pwm, 0, PWM_PERCENTAGE_TO_WIDTH(pwm, Voltage));
    pwmEnableChannel(pwm, 1, PWM_PERCENTAGE_TO_WIDTH(pwm, 0));
  }
  else if (DirectionOfRotation == COUNTERCLOCKWISE_ROTATION){
    pwmEnableChannel(pwm, 0, PWM_PERCENTAGE_TO_WIDTH(pwm, 0));
    pwmEnableChannel(pwm, 1, PWM_PERCENTAGE_TO_WIDTH(pwm, Voltage));
  }
}
