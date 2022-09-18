#ifndef INCLUDE_MOTOR_CONTROL_H_
#define INCLUDE_MOTOR_CONTROL_H_

#include <motor_lld.h>
#include <modbusRegister.h>


// Motor configuration.
#define MOTOR_DATA_RATE                     20 // Data rate is 50. [1/50 is 20 milliseconds].
#define MOTOR_STEP_TO_CHANGE_VOLTAGE        100 // The step size by which we will change the voltage during the period. 100 - 1%


#define MOTOR_ZERO_VOLTAGE                  0 // Zero voltage value for motor start position.

// Possible state of the motor.
#define MOTOR_STATE_RUNNING                 1
#define MOTOR_STATE_STOPPED                 0
/*
 *  @brief  Coefficients for converting speed in revolutions per minute
 *          to voltage as a percentage of the maximum voltage and vice versa.
 *
 *  @note   Max voltage value of motor is 24 V.
 *
 *  @notr   Max rotational speed is 1000 rpm.
 *
 *  @note   COEF_RPM_TO_VOLTS_IN_PERSENTAGE     10  [10000 / 1000 rpm| 10000 is 100%]
 *          COEF_RPM_TO_VOLTS_IN_PERSENTAGE     0.1 [1000 rpm / 10000| 10000 is 100%]
 */
#define COEF_RPM_TO_VOLTS_IN_PERSENTAGE     10
#define COEF_VOLTS_IN_PERSENTAGE_TO_RPM     0.1


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
