#include <motor_control.h>

/*
 *  @brief  User defined values placed in variables.
 *
 *  @note   Values: The direction of rotation, the voltage and the state.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @note   They are used to control the motor.
 */

int16_t MotorRequiredVoltage; // New voltage that is set by the user.
int16_t MotorCurrentVoltage; // The current value of motor voltage.



/*
 *  @brief  Gradually changes the motor voltage from current value to setpoint.
 *
 *  @note   Takes into account the direction of voltage change.
 *
 *  @note   Increases or decreases the voltage by MOTOR_STEP_TO_CHANGE_VOLTAGE value.
 *          The last increase or decrease in value occurs up to the set value.
 *
 *  @note   If the value doesn't change, then nothing happens.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @notapi
 */
void update_motor_voltage(void){
  MotorRequiredVoltage = MB_READ_REG_INT16(DATA_MOTOR_REQUIRED_VOLTAGE); // Reading from the modbus
  // Check a percentage of the maximum voltage value.
  if (MotorRequiredVoltage > MAX_VOLTAGE_VALUE) MotorRequiredVoltage = MAX_VOLTAGE_VALUE;
  else if (MotorRequiredVoltage < -MAX_VOLTAGE_VALUE) MotorRequiredVoltage = -MAX_VOLTAGE_VALUE;

  // When the voltage should be increased. And the voltage difference is greater than MOTOR_STEP_TO_CHANGE_VOLTAGE.
  if ((MotorRequiredVoltage - MotorCurrentVoltage) >= MOTOR_STEP_TO_CHANGE_VOLTAGE){
    MotorCurrentVoltage += MOTOR_STEP_TO_CHANGE_VOLTAGE;
  }
  // When the voltage should be decreased. And the voltage difference is less than minus MOTOR_STEP_TO_CHANGE_VOLTAGE.
  else if ((MotorRequiredVoltage - MotorCurrentVoltage) <= -MOTOR_STEP_TO_CHANGE_VOLTAGE){
    MotorCurrentVoltage -= MOTOR_STEP_TO_CHANGE_VOLTAGE;
  }
  // When the voltage should be increased or decreased. And the voltage difference is in range:
  // (-MOTOR_STEP_TO_CHANGE_VOLTAGE, MOTOR_STEP_TO_CHANGE_VOLTAGE).
  else{
    MotorCurrentVoltage = MotorRequiredVoltage;
  }

  motorSetVoltage(MotorCurrentVoltage);
  MB_WRITE_REG_INT16(DATA_MOTOR_CURRENT_VOLTAGE, MotorCurrentVoltage); // Writing from the modbus
}


/*
 *  @brief  Starts another thread to set the specified voltage to the motor.
 *
 *  @note   You need to set: the voltage, the direction of rotation and the state of the motor.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @notapi
 */
static thread_t *tp_motor;
static THD_WORKING_AREA(waMotor, 256);// 256 - stack size

static THD_FUNCTION(motorThread, arg)
{
    (void)arg; // just to avoid warnings
    chRegSetThreadName("Motor control thread");
    systime_t time = chVTGetSystemTime();
    while( !chThdShouldTerminateX() ){
      update_motor_voltage();
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( MOTOR_DATA_RATE ) );
    }
    chThdExit(MSG_OK);
}

/*
 *  @brief  Initializes the motor and starts another thread to set specified voltage to the motor.
 *
 *  @note   You need to set: the voltage, the direction of rotation and the state of the motor.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 */
msg_t motorInit(void){
  motorSimpleInit();
  // Set the start motor parameters.
  MotorRequiredVoltage = MOTOR_ZERO_VOLTAGE;
  MotorCurrentVoltage = MOTOR_ZERO_VOLTAGE;
  tp_motor = chThdCreateStatic(waMotor, sizeof(waMotor), NORMALPRIO, motorThread, NULL);
  return MSG_OK;
}

/*
 *  @brief  Stops the motor and the motor thread.
 *
 *  @param[out]    msg   A message is about if thread is stopped or not.
 *
 *  @note   Not verified.
 */
msg_t motorUninit(void){
  chThdTerminate(tp_motor);
  msg_t msg = chThdWait(tp_motor);
  motorSimpleUninit();
  // Resetting the motor current parameters.
  MotorRequiredVoltage = MOTOR_ZERO_VOLTAGE;
  MotorCurrentVoltage = MOTOR_ZERO_VOLTAGE;
  // Writing data to the modbus
  MB_WRITE_REG_INT16(DATA_MOTOR_REQUIRED_VOLTAGE, MotorRequiredVoltage);
  MB_WRITE_REG_INT16(DATA_MOTOR_CURRENT_VOLTAGE, MotorCurrentVoltage);

  return msg;
}

/*
 *  @brief  Returns the current voltage value.
 *
 *  @param[out]   MotorCurrentVoltage  The current value of motor voltage.
 *
 *  @note   For debugging only.
 */
int16_t getMotorCurrentVoltage(void){
  return MotorCurrentVoltage;
}



/*
 *  @brief  Sets the current motor voltage.
 *
 *  @param[in]   Voltage   New voltage that is set by the user.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 *
 *  @note   For debugging only.
 */
void setMotorVoltage(int16_t Voltage){
  MotorRequiredVoltage = Voltage;
}

