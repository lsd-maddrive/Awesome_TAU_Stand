#ifndef INCLUDE_MOTOR_CONTROL_H_
#define INCLUDE_MOTOR_CONTROL_H_

#include <motor_lld.h>


// Motor configuration.
#define MOTOR_DATA_RATE 20 // Data rate is 50. [1/50 is 20 milliseconds].
#define MOTOR_STEP_TO_CHANGE_VOLTAGE 100 // The step size by which we will change the voltage during the period. 100 - 1%


#define MOTOR_ZERO_VOLTAGE 0 // Zero voltage value for motor start position.

// Possible state of the motor.
#define MOTOR_STATE_RUNNING true
#define MOTOR_STATE_STOPPED false



/*
 *  @brief  Initializes the motor and starts another thread to set specified voltage to the motor.
 *
 *  @note   You need to set: the voltage, the direction of rotation and the state of the motor.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 */
void motorInit(void);

/*
 *  @brief  Stops the motor and the motor thread.
 *
 *  @param[out]    msg   A message is about if thread is stopped or not.
 *
 *  @note   Not verified.
 */
msg_t motorUninit(void);

/*
 *  @brief  Returns the current voltage value.
 *
 *  @param[out]   MotorCurrentVoltage  The current value of motor voltage.
 *
 *  @note   For debugging only.
 */
int16_t getMotorCurrentVoltage(void);

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
void setMotorVoltage(int16_t Voltage);

#endif /* INCLUDE_MOTOR_CONTROL_H_ */
