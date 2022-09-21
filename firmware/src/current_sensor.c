#include <current_sensor.h>

static float current; // Current value calculated from the voltage in AMPS.

/*
 *  @brief  Starts another thread to read the voltage from the sensor and
 *          converts it to a current value.
 *
 *  @notapi
 */
static THD_WORKING_AREA(waCurrentSensor, 256);// 256 - stack size

static THD_FUNCTION(currentSensorThread, arg)
{
    arg = arg; // just to avoid warnings

    systime_t time = chVTGetSystemTime();
    while( true ){
      current = sensorM3421Read()*CURRENT_COEF; // Converts the voltage to a current value.
      MB_WRITE_REG_FLOAT(DATA_CURRENT_SENSOR_CURRENT, current); // Writing data to the modbus
      if (chThdShouldTerminateX() == TRUE) chThdExit(MSG_OK);
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( ADC_DATA_RATE ) );

    }
}

/*
 *  @brief  Initializes the current sensor and starts another thread to read
 *          the current value from it.
 *
 *  @note   Used m3421 ADC.
 *  @note   One-Shot mode may not be working.
 */
msg_t currentSensorInit(void){
  sensorM3421Init();
  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS)
    chThdCreateStatic(waCurrentSensor, sizeof(waCurrentSensor), NORMALPRIO, currentSensorThread, NULL);
  return MSG_OK;
}

/*
 * @brief  Stops I2C (if it's enabled) and current sensor thread.
 *
 * @param[out]    msg   A message is about if thread is stopped or not.
 */
msg_t currentSensorUninit(void){
  chThdTerminate((thread_t *)currentSensorThread);
  msg_t msg = chThdWait((thread_t *)currentSensorThread);
  i2cSimpleStop();
  return msg;
}


/*
 * @brief Returns the converted current from the voltage in AMPS.
 *
 * @param[out]  current   Current value calculated from the voltage in AMPS,
 *                        taking into account the sign.
 *
 */
float getCurrent(void){
  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS)  return current;
  return sensorM3421Read()*CURRENT_COEF;
}
