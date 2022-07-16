#include <common.h>
#include <lld_i2c.h>
#include <sensor_m3421.h>
#include <string.h>
#include <math.h>

/*
 * @brief   Initializes variables for working with sensor configuration.
 *
 * @note    gain - Signal gain. 0 - 1 V/V, 1 - 2 V/V, 2 - 4 V/V, 3 - 8V/V.
 *          mode - Conversion Mode Bit. 0 - One-Shot, 1 - Continuous.
 *          res -  Sample Rate Selection/bit selection. 0 - 12 bits, 1 - 14 bits,
 *                 2 - 16 bits, 3 - 18 bits.
 *
 * @ Do not set the wrong values for variables! It can lead to disaster.
 */
typedef struct sensor_conf {
    uint8_t gain;
    bool mode;
    uint8_t res;
}sensor_conf_t;

//You can set required parameters here
sensor_conf_t conf = {
    .gain = 0, //0 - 1 V/V, 1 - 2 V/V, 2 - 4 V/V, 3 - 8V/V.
    .mode = 1, //0 - One-Shot, 1 - Continuous.
    .res = 2 //0 - 12 bits, 1 - 14 bits, 2 - 16 bits, 3 - 18 bits.
};


uint8_t config = {0};
float volts;

/*
 * @brief   Builds configuration by given variables (gain, res, mode)
 *
 * @param[out] config   Will be used to configure the sensor operation
 *
 * @notapi
 */
int8_t sensor_m3421_make_config(void){

  config = 0; //resets configuration.

  if (conf.mode == 1) config |= 0x10; // Conversion Mode.

  switch(conf.gain){ // Signal gain.
  case 1:
    config |= 0x01;
    break;
  case 2:
    config |= 0x02;
    break;
  case 3:
    config |= 0x01 + 0x02;
    break;
  default: // gain = 0.
    break;
  }

  switch(conf.res){ // Sample Rate Selection/bit selection.
  case 1:
    config |= 0x04;
    break;
  case 2:
    config |= 0x08;
    break;
  case 3:
    config |= 0x04 + 0x08;
    break;
  default: // res = 0
    break;
  }
  return config;
}

/*
 * @brief   Initializes the sensor.
 *
 * @note    Launches I2C.
 * @note    When the state of the Conversion Mode (mode) is Continuous (1),
 *          set up the sensor with the given configuration.
 *
 */
void sensor_m3421_init(void){
  chSysInit();
  halInit();
  i2cStartUp(); //Launches I2C.
  if (conf.mode == 1){ // Builds configuration and initializes the sensor.
    config = sensor_m3421_make_config();
    i2cSimpleWrite(SENSOR_M3421_ADDR, &config, 1);
  }
}

/*
 * @brief  Convert the obtained value from ADC to a voltage measured in volts.
 *
 * @param[in]   val       The result in bits received from the ADC.
 *              n_bits    Number of bits set in "res" variable
 *                        (Sample Rate Selection/bit selection).
 *
 * @param[out]  volts     The result of voltage measurments in VOLTS,
 *                        taking into account the gain and the sign.
 *
 * @notapi
 */
float lsb2v(int16_t val, uint8_t n_bits){
  volts = val*(2.048/pow(2, n_bits-1));//Converts the data from ADC to a voltage.

  switch(conf.gain){ // Takes into account the gain.
  case 1:
    volts = volts/2;
    break;
  case 2:
    volts = volts/4;
    break;
  case 3:
     volts = volts/8;
     break;
  default:// gain = 0
    break;
  }
  return volts;
}

/*
 * @brief   Measures the voltage and convert the result from ADC to volts.
 *
 * @note    When the state of the Conversion Mode (mode) is One-Shot (0),
 *          set up the sensor with the given configuration.
 */
void sensor_m3421_read(void){

  uint8_t rxbuf[4] = {0}; // It stores the read data from the ADC.
  uint8_t add = {0}; // It is needed to fill the array.
  int32_t val; // It is a sorted array of "rxbuf".
  uint8_t n; //Number of bits set in "res" (Sample Rate Selection/bit selection).

  if (conf.mode == 0){ // Builds configuration and initializes the sensor.
      config = sensor_m3421_make_config();
      i2cSimpleWrite(SENSOR_M3421_ADDR, &config, 1);
  }

  i2cSimpleRead(SENSOR_M3421_ADDR, rxbuf, 4); // Reads data from the ADC.


  if (rxbuf[0]&(1<<7))add = ~add; // Takes into account the sign

  switch (conf.res){ // Sorts "rxbuf" and fill the array
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

  volts = lsb2v(val, n); // Converts the data from ADC to volts.
}

/*
 * @brief Returns measured voltage value in VOLTS.
 *
 * @param[out]  volts   The result of voltage measurments in VOLTS,
 *                      taking into account the gain and the sign.
 */
float get_volts(void){
  return volts;
}



