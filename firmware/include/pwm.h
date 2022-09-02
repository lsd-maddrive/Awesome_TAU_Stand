#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#include <common.h>

#define CLOCKWISE_ROTATION  0
#define COUNTERCLOCKWISE_ROTATION 1

void pwmInit(void);

void pwmCheakingDirectionAndVoltage(uint8_t DirectionOfRotation, uint8_t Voltage);


#endif /* INCLUDE_PWM_H_ */
