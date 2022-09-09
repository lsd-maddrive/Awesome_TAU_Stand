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
static motorParam motor = {
  .NewDirectionOfRotation = MOTOR_NEW_DIRECTION_OF_ROTATION , // New direction of rotation that is set by the user.
  .PresentDirectionOfRotation = MOTOR_PRESENT_DIRECTION_OF_ROTATION , // The current direction of motor rotation.
  .NewVoltage = MOTOR_NEW_VOLTAGE , // New voltage that is set by the user.
  .PresentVoltage = MOTOR_PRESENT_VOLTAGE , // The current value of motor voltage.
  .State = MOTOR_STATE // The state of the motor that indicates whether it is running or not.
};

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
 *  @notapi
 */
void update_motor_voltage(void){
  // When the voltage should be increased. And the voltage difference is greater than MOTOR_STEP_TO_CHANGE_VOLTAGE.
  if ((motor.NewVoltage - motor.PresentVoltage) >= MOTOR_STEP_TO_CHANGE_VOLTAGE){
    motor.PresentVoltage += MOTOR_STEP_TO_CHANGE_VOLTAGE;
    motorSetVoltage(motor.PresentDirectionOfRotation, motor.PresentVoltage);
  }
  // When the voltage should be decreased. And the voltage difference is less than minus MOTOR_STEP_TO_CHANGE_VOLTAGE.
  else if ((motor.NewVoltage - motor.PresentVoltage) <= -MOTOR_STEP_TO_CHANGE_VOLTAGE){
    motor.PresentVoltage -= MOTOR_STEP_TO_CHANGE_VOLTAGE;
    motorSetVoltage(motor.PresentDirectionOfRotation, motor.PresentVoltage);
  }
  // When the voltage should be increased or decreased. And the voltage difference is in range:
  // (-MOTOR_STEP_TO_CHANGE_VOLTAGE, 0) or (0, MOTOR_STEP_TO_CHANGE_VOLTAGE).
  else if ((motor.NewVoltage - motor.PresentVoltage) != 0){
    motor.PresentVoltage += (motor.NewVoltage - motor.PresentVoltage);
    motorSetVoltage(motor.PresentDirectionOfRotation, motor.PresentVoltage);
  }
}

/*
 *  @brief  Checks if the direction of rotation has changed or not.
 *
 *  @note   If the direction of rotation has changed, the motor will stop and set the current
 *          voltage to zero and change the current direction of rotation to the specified one.
 *
 *  @note   It takes some time for the motor to stop. This time is set in the MOTOR_STOP_SLEEP_MILLISECONDS variable.
 *
 *  @notapi
 */
void check_direction_of_rotation(void){
  if (motor.NewDirectionOfRotation != motor.PresentDirectionOfRotation){
    motorSimpleStop();
    chThdSleepMilliseconds(MOTOR_STOP_SLEEP_MILLISECONDS);

    motor.PresentVoltage = 0;
    motor.PresentDirectionOfRotation = motor.NewDirectionOfRotation;
  }
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
static THD_WORKING_AREA(waMotor, 256);// 256 - stack size

static THD_FUNCTION(motorThread, arg)
{
    (void)arg; // just to avoid warnings
    systime_t time = chVTGetSystemTime();
    while( true ){
      // Checking if the motor is running.
      if (motor.State == true){
        // Check if the voltage or the direction of rotation was changed.
        check_direction_of_rotation();
        update_motor_voltage();
      }
      else motorSimpleStop(); // If the motor is not running.
      if (chThdShouldTerminateX() == TRUE) chThdExit(MSG_OK);
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( MOTOR_DATA_RATE ) );
    }
}

/*
 *  @brief  Initializes the motor and starts another thread to set specified voltage to the motor.
 *
 *  @note   You need to set: the voltage, the direction of rotation and the state of the motor.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 */
void motorInit(void){
  motorSimpleInit();
  chThdCreateStatic(waMotor, sizeof(waMotor), NORMALPRIO, motorThread, NULL);
}

/*
 *  @brief  Stops the motor and the motor thread.
 *
 *  @param[out]    msg   A message is about if thread is stopped or not.
 *
 *  @note   Not verified.
 */
msg_t motorUninit(void){
  chThdTerminate((thread_t *)motorThread);
  msg_t msg = chThdWait((thread_t *)motorThread);
  motorSimpleUninit();
  return msg;
}

/*
 *  @brief  Returns the current voltage value.
 *
 *  @param[out]   motor.PresentVoltage  The current value of motor voltage.
 *
 *  @note   For debugging only.
 */
uint16_t getMotorPresentVoltage(void){
  return motor.PresentVoltage;
}

/*
 *  @brief  Returns the current direction of rotation.
 *
 *  @param[out]   motor.PresentDirectionOfRotation  The current direction of motor rotation.
 *
 *  @note   For debugging only.
 */
uint8_t getMotorPresentDirectionOfRotation(void){
  return motor.PresentDirectionOfRotation;
}

