#ifndef INCLUDE_CURRENT_SENSOR_H_
#define INCLUDE_CURRENT_SENSOR_H_


/*
 *  @brief  Initializes the current sensor and starts a second thread to read
 *          the current value from it.
 *
 *  @note   Used m3421 ADC.
 */
void currentSensorInit(void);

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

#endif /* INCLUDE_CURRENT_SENSOR_H_ */
