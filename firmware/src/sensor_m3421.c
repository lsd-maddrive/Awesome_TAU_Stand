#include <common.h>
#include <lld_i2c.h>
#include <sensor_m3421.h>
#include <string.h>
#include <math.h>
#include <terminal_write.h>

static float volts; // The result of voltage measurments in VOLTS.

uint8_t config = {0}; // Contains the specified sensor configuration
uint8_t rxbuf[3] = {0}; // It stores the read data from the ADC.
uint8_t add = {0}; // It is needed to fill the array.
int32_t val; // It is a sorted array of "rxbuf".
uint8_t n; //Number of bits set in "res" (Sample Rate Selection/bit selection).

/*
 * @brief   Builds configuration by given variables (gain, res, mode)
 *
 * @param[out] config   Will be used to configure the sensor operation
 *
 * @notapi
 */
int8_t sensor_m3421_make_config(void){

  config = 0; //resets configuration.

  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS) config |= 0x10; // Conversion Mode.

  switch(ADC_GAIN_ROUTINE){ // Signal gain.
  case ADC_GAIN_2:
    config |= 0x01;
    break;
  case ADC_GAIN_4:
    config |= 0x02;
    break;
  case ADC_GAIN_8:
    config |= 0x01 + 0x02;
    break;
  default: // ADC_GAIN_1.
    break;
  }

  //We will use only 14 bits.
  switch(ADC_RES_ROUTINE){ // Sample Rate Selection/bit selection.
  case ADC_RES_14_BITS:
    config |= 0x04;
    break;
  case ADC_RES_16_BITS:
    config |= 0x08;
    break;
  case ADC_RES_18_BITS:
    config |= 0x04 + 0x08;
    break;
  default: // ADC_RES_12_BITS
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
void sensorM3421Init(void){
  i2cStartUp(); //Launches I2C.

  /*
   * Builds configuration, initializes the sensor and starts the second thread
   * to read the voltage from the ADC and converts it to a current value.
   */
  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS){ //
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

  switch(ADC_GAIN_ROUTINE){ // Takes into account the gain.
  case ADC_GAIN_2:
    volts = volts*0.5;
    break;
  case ADC_GAIN_4:
    volts = volts*0.25;
    break;
  case ADC_GAIN_8:
     volts = volts*0.125;
     break;
  default:// ADC_GAIN_1
    break;
  }
  return volts;
}

/*
 * @brief   Measures the voltage and convert the result from ADC to volts.
 *
 * @param[out]  volts   The result of voltage measurments in VOLTS,
 *                      taking into account the gain and the sign.
 *
 * @note    When the state of the Conversion Mode (mode) is One-Shot (0),
 *          set up the sensor with the given configuration.
 * @note    We will use only 14 bits.
 */


float sensorM3421Read(void){

  add = 0; // It is needed to fill the array.


  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS){ // Builds configuration and initializes the sensor.
      config = sensor_m3421_make_config();
      i2cSimpleWrite(SENSOR_M3421_ADDR, &config, 1);
  }

  i2cSimpleRead(SENSOR_M3421_ADDR, rxbuf, 3); // Reads data from the ADC.
  if (~rxbuf[2]&(1<<7)){// Cheaks if  output register has been updated with the
                        // latest conversion data

    if (rxbuf[0]&(1<<7))add = ~add; // Takes into account the sign

    switch (ADC_RES_ROUTINE){ // Sorts "rxbuf" and fill the array
    case ADC_RES_12_BITS:
      val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
      n = 12;
      break;
    case ADC_RES_14_BITS:
      val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
      n = 14;
      break;
    case ADC_RES_16_BITS:
      val = (add << 24 | add << 16 | rxbuf[0] << 8) | rxbuf[1];
      n = 16;
      break;
    case ADC_RES_18_BITS:
      val = (add << 24 | rxbuf[0] << 16) | rxbuf[1] << 8 | rxbuf[2];
      n = 18;
      break;
    default:
      break;
    }
    //dbgPrintf("%d, %d, %d\r\n", rxbuf[0],rxbuf[1],rxbuf[2]);
    volts = lsb2v(val, n); // Converts the data from ADC to volts.
  }
  return volts;
}

/*
 * @brief Returns measured voltage value in VOLTS.
 *
 * @param[out]  volts   The result of voltage measurments in VOLTS,
 *                      taking into account the gain and the sign.
 */
float getVolts(void){
  return volts;
}

/*
 *  @brief  Returns the config byte read from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] rxbuf[2]    The config byte read from the ADC.
 */
uint8_t getConfig(void){
  return rxbuf[2];
}

/*
 *  @brief  Returns a sorted array of "rxbuf" from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] val    a sorted array of "rxbuf" from the ADC.
 */
int32_t getVal(void){
  return val;
}

/*
 *  @brief  Returns the read data from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] *rxbuf  Pointer to an array that stores the read data from the ADC.
 */
uint8_t getRxbuf(void){
  return *rxbuf;
}



