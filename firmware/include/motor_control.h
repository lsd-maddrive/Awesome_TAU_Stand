#ifndef INCLUDE_MOTOR_CONTROL_H_
#define INCLUDE_MOTOR_CONTROL_H_

#include <motor_lld.h>


// Motor configuration.
#define MOTOR_DATA_RATE 20 // Data rate is 50. [1/50 is 20 milliseconds].
#define MOTOR_STOP_SLEEP_MILLISECONDS 1000  // It takes some time for the motor to stop.
#define MOTOR_STEP_TO_CHANGE_VOLTAGE 100 // The step size by which we will change the voltage during the period.


#define MOTOR_PRESENT_DIRECTION_OF_ROTATION CLOCKWISE_ROTATION // The current direction of motor rotation.
#define MOTOR_PRESENT_VOLTAGE 0 // Current voltage value.

// Possible state of the motor.
#define MOTOR_STATE_TRUE true
#define MOTOR_STATE_FALSE false


// Is set by user
#define MOTOR_NEW_DIRECTION_OF_ROTATION CLOCKWISE_ROTATION
/*
 *  @brief  New voltage that is set by the user.
 *
 *  @note   The voltage is setted as a percentage of the maximum voltage value of motor.
 *          Can be in range [0, 9500]. 100 is 1%. 100% is not used because it can led to breakdowns.
 */
#define MOTOR_NEW_VOLTAGE 5000
#define MOTOR_STATE MOTOR_STATE_TRUE // The state of the motor that indicates whether it is running or not.



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
typedef struct
{
    uint8_t NewDirectionOfRotation ; // New direction of rotation that is set by the user.
    uint8_t PresentDirectionOfRotation; // The current direction of motor rotation.
    uint16_t NewVoltage; // New voltage that is set by the user.
    uint16_t PresentVoltage; // The current value of motor voltage.
    bool State; // The state of the motor that indicates whether it is running or not.
} motorParam;

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
 *  @param[out]   motor.PresentVoltage  The current value of motor voltage.
 *
 *  @note   For debugging only.
 */
uint16_t getMotorPresentVoltage(void);

/*
 *  @brief  Returns the current direction of rotation.
 *
 *  @param[out]   motor.PresentDirectionOfRotation  The current direction of motor rotation.
 *
 *  @note   For debugging only.
 */
uint8_t getMotorPresentDirectionOfRotation(void);

#endif /* INCLUDE_MOTOR_CONTROL_H_ */
