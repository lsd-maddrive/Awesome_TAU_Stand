#ifndef INCLUDE_CURRENT_SENSOR_H_
#define INCLUDE_CURRENT_SENSOR_H_

#include <sensor_m3421.h>
#include <modbusRegister.h>

#define CURRENT_COEF 5/(8*0.075) // 8 - gain ofisolation amplifier.
                                       // Shunt operates 5 A at 75 mV.
/*
 *  @brief  Initializes the current sensor and starts another thread to read
 *          the current value from it.
 *
 *  @note   Used m3421 ADC.
 *  @note   One-Shot mode may not be working.
 */
msg_t currentSensorInit(void);

/*
 * @brief  Stops I2C (if it's enabled) and current sensor thread.
 *
 * @param[out]    msg   A message is about if thread is stopped or not.
 */
msg_t currentSensorUninit(void);

/*
 * @brief Returns the converted current from the voltage in AMPS.
 *
 * @param[out]  current   Current value calculated from the voltage in AMPS,
 *                        taking into account the sign.
 */
float getCurrent(void);

#endif /* INCLUDE_CURRENT_SENSOR_H_ */
