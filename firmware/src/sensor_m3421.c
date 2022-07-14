#include <common.h>
#include <lld_i2c.h>
#include <sensor_m3421.h>
#include <string.h>
#include <math.h>

uint8_t mode = 1;//0 - One-Shot, 1 - Continuous.
uint8_t gain = 0;//0 - 1 V/V, 1 - 2 V/V, 2 - 4 V/V, 3 - 8V/V.
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
  sensor_m3421_make_config();
}


uint8_t sensor_m3421_bits(void){// сколько нужно байт
  uint8_t n_bytes;
  if (res == 3)n_bytes = 4;
  else n_bytes = 3;
  return n_bytes;
}

float lsb2v(int16_t val, uint8_t sign, uint8_t n_bits){
  volts = val*(2.048/pow(2, n_bits-1));//истинное значение без учета КУ и знака

  if (sign == 1) volts = -volts; // учитываем знак

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
  i2cSimpleWrite(SENSOR_M3421_ADDR, &config, 1);
  uint8_t rxbuf[sensor_m3421_bits()];
  memset( rxbuf, 0, sensor_m3421_bits()*sizeof(int) );
  i2cSimpleRead(SENSOR_M3421_ADDR, rxbuf, sensor_m3421_bits());
  uint16_t val;
  uint8_t sign, n;


  if (~rxbuf[0]&(1<<7))sign = 0;// узнаём знак напряжения
  else sign = 1;

  switch (res){ // преобразуем результат
  case 0:
    rxbuf[0]=rxbuf[0] & 0x07;
    val = (rxbuf[0] << 8) | rxbuf[1];
    n = 12;
    break;
  case 1:
    rxbuf[0]=rxbuf[0] & 0x1F;
    val = (rxbuf[0] << 8) | rxbuf[1];
    n = 14;
    break;
  case 2:
    rxbuf[0]=rxbuf[0] & 0x7F;
    val = (rxbuf[0] << 8) | rxbuf[1];
    n = 16;
    break;
  case 3:
    rxbuf[0]=rxbuf[0] & 0x01;
    val = (rxbuf[0] << 16) | rxbuf[1] << 8 | rxbuf[0];
    n = 18;
    break;
  default:
    break;
  }

  volts = lsb2v(val, sign, n);
}


float get_volts(void){
  return volts;
}


