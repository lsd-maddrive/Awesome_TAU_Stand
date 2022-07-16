#ifndef INCLUDE_SENSOR_M3421_H_
#define INCLUDE_SENSOR_M3421_H_

#define SENSOR_M3421_ADDR 0b1101000

/*
 * @brief   Initializes the sensor and launches I2C.
 */
void sensor_m3421_init(void);

/*
 * @brief Returns measured voltage value in VOLTS taking into account the
 *        gain and the sign.
 */
float get_volts(void);

/*
 * @brief   Measures the voltage and convert the result from ADC to volts.
 */
void sensor_m3421_read(void);

#endif /* INCLUDE_SENSOR_M3421_H_ */
