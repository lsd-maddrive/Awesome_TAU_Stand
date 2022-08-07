#include "common.h"
#include <sensor_m3421.h>
#include "current_sensor.h"

static float current; // Current value calculated from the voltage in AMPS.

/*
 *  @brief  Starts the second thread to read the voltage from the sensor and
 *          converts it to a current value.
 *
 *  @notapi
 */
static THD_WORKING_AREA(waCurrentSensor, 256);// 256 - stack size

static THD_FUNCTION(currentSensor, arg)
{
    arg = arg; // just to avoid warnings

    systime_t time = chVTGetSystemTime();
    while( true ){
      current = sensorM3421Read()*CURRENT_COEF; // Converts the voltage to a current value.
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( ADC_DATA_RATE ) );
    }
}

/*
 *  @brief  Initializes the current sensor and starts a second thread to read
 *          the current value from it.
 *
 *  @note   Used m3421 ADC.
 *  @note   One-Shot mode may not be working.
 */
void currentSensorInit(void){
  sensorM3421Init();
  if (ADC_MODE_ROUTINE == ADC_MODE_CONTINUOUS)
    chThdCreateStatic(waCurrentSensor, sizeof(waCurrentSensor), NORMALPRIO, currentSensor, NULL);

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
