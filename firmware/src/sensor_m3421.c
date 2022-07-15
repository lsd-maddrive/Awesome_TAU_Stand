#include <common.h>
#include <lld_i2c.h>
#include <sensor_m3421.h>
#include <string.h>
#include <math.h>
#include <terminal_write.h>


//struct adc_conf {
//    uint8_t gain;
//    bool mode;
//    uint8_t res;
//};
//
//typedef struct adc_conf adc_conf_t;
//
//adc_conf_t conf = {
//    .gain = 2,
//    .mode = 0
//};

uint8_t mode = 1;//0 - One-Shot, 1 - Continuous.
uint8_t gain = 1;//0 - 1 V/V, 1 - 2 V/V, 2 - 4 V/V, 3 - 8V/V.
uint8_t res = 2; //0 - 12 bits, 1 - 14 bits, 2 - 16 bits, 3 - 18 bits.
uint8_t config = {0};
float volts;

int8_t sensor_m3421_make_config(void){


  config = 0;

  if (mode == 1) config |= 0x10; // режим работы
  switch(gain){ //  коэф. усиления
  case 1:
    config |= 0x01;
    break;
  case 2:
    config |= 0x02;
    break;
  case 3:
    config |= 0x01 + 0x02;
    break;
  default:
    break;
  }

  switch(res){ //  выбор битности
  case 1:
    config |= 0x04;
    break;
  case 2:
    config |= 0x08;
    break;
  case 3:
    config |= 0x04 + 0x08;
    break;
  default:
    break;
  }
  return config;
}

void sensor_m3421_init(void){
  chSysInit();
  halInit();
  i2cStartUp();
  config = sensor_m3421_make_config();
  i2cSimpleWrite(SENSOR_M3421_ADDR, &config, 1);
}


//uint8_t sensor_m3421_bits(void){// сколько нужно байт
//  uint8_t n_bytes;
//  if (res == 3)n_bytes = 4;
//  else n_bytes = 3;
//  return n_bytes;
//}

float lsb2v(int16_t val, uint8_t n_bits){
  volts = val*(2.048/pow(2, n_bits-1));//истинное значение без учета КУ и знака

  switch(gain){// учитываем КУ
  case 1:
    volts = volts/2;
    break;
  case 2:
    volts = volts/4;
    break;
  case 3:
     volts = volts/8;
     break;
  default:
    break;
  }
  return volts;
}

void sensor_m3421_read(void){ // считываем напряжение

  uint8_t rxbuf[4] = {0};
  uint8_t add = {0};
  i2cSimpleRead(SENSOR_M3421_ADDR, rxbuf, 4);
  int32_t val;
  uint8_t n;

  if (rxbuf[0]&(1<<7))add = ~add;// узнаём знак напряжения

  switch (res){ // преобразуем результат
  case 0:
    val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
    n = 12;
    break;
  case 1:
    val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
    n = 14;
    break;
  case 2:
    val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
    n = 16;
    break;
  case 3:
    val = (add << 24 | rxbuf[0] << 16) | rxbuf[1] << 8 | rxbuf[0];
    n = 18;
    break;
  default:
    break;
  }

  volts = lsb2v(val, n);
}


float get_volts(void){
  return volts;
}

uint8_t get_config(void){
  return config;
}


