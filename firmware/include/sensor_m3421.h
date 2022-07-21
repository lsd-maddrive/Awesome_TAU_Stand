#ifndef INCLUDE_SENSOR_M3421_H_
#define INCLUDE_SENSOR_M3421_H_

#define SENSOR_M3421_ADDR 0b1101000 // Address of used ADC.

#define ADC_DATA_RATE 0.01666 // At 14 bits data rate is 60 PSP. 1/60 = 0.01666.
#define CURRENT_COEF 5/(8*75*pow(10, -3)) // 8 - gain ofisolation amplifier.
                                       // Shunt operates 5 A at 75 mV.

//List of posible settings.
//Signal gain. 0 - 1 V/V, 1 - 2 V/V, 2 - 4 V/V, 3 - 8V/V.
#define ADC_GAIN_1 0
#define ADC_GAIN_2 1
#define ADC_GAIN_4 2
#define ADC_GAIN_8 3
//Conversion Mode Bit.
#define ADC_MODE_ONE_SHOT 0
#define ADC_MODE_CONTINUOUS 1
//Sample Rate Selection/bit selection.
#define ADC_RES_12_BITS 0
#define ADC_RES_14_BITS 1
#define ADC_RES_16_BITS 2
#define ADC_RES_18_BITS 3

// Selection of settings to run
#define ADC_GAIN_ROUTINE ADC_GAIN_1
#define ADC_MODE_ROUTINE ADC_MODE_CONTINUOUS
#define ADC_RES_ROUTINE ADC_RES_14_BITS//We will use only 14 bits.

/*
 * @brief   Initializes the sensor.
 *
 * @note    Launches I2C.
 * @note    When the state of the Conversion Mode (mode) is Continuous (1),
 *          set up the sensor with the given configuration.
 *
 */
void sensorM3421Init(void);

/*
 * @brief Returns measured voltage value in VOLTS.
 *
 * @param[out]  volts   The result of voltage measurments in VOLTS,
 *                      taking into account the gain and the sign.
 */
float getVolts(void);

/*
 * @brief Returns the converted current from the voltage in AMPS.
 *
 * @param[out]  current   Current value calculated from the voltage in AMPS,
 *                        taking into account the sign.
 */
float getCurrent(void);

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
float sensorM3421Read(void);

/*
 *  @brief  Returns the config byte read from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] rxbuf[2]    The config byte read from the ADC.
 */
uint8_t getConfig(void);

/*
 *  @brief  Returns a sorted array of "rxbuf" from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] val    a sorted array of "rxbuf" from the ADC.
 */
int32_t getVal(void);

/*
 *  @brief  Returns the read data from the ADC.
 *
 *  @not    Just for error checking.
 *
 *  @param[out] *rxbuf  Pointer to an array that stores the read data from the ADC.
 */
uint8_t getRxbuf(void);

#endif /* INCLUDE_SENSOR_M3421_H_ */
