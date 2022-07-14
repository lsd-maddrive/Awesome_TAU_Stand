#include "lld_i2c.h"
// Задаем конфигурацию драйвера, частота тактирования i2c 54МГц
static const I2CConfig i2c1_conf = {
    .timingr = STM32_TIMINGR_PRESC(14U)  |
    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
    .cr1 = 0,
    .cr2 = 0
};

// Запишем указатель на драйвер в переменную
static I2CDriver* i2c1 =  &I2CD1;

void i2cStartUp(void){
  i2cStart(i2c1, &i2c1_conf);
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(4) |
                        PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                        PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(4) |
                        PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                        PAL_STM32_PUPDR_PULLUP);
}

msg_t i2cSimpleWrite(uint8_t addr, uint8_t *buf, uint8_t n){
  return i2cMasterTransmitTimeout(i2c1, addr, buf, n, NULL, 0, 1000);
}

msg_t i2cSimpleRead(uint8_t addr, uint8_t *buf, uint8_t n){
 return i2cMasterReceive(i2c1, addr, buf, n);
}

msg_t i2cRegisterRead(uint8_t addr, uint8_t raddr, uint8_t *buf, uint8_t n){
 return i2cMasterTransmit(i2c1, addr, &raddr, 1, buf, n);
}

