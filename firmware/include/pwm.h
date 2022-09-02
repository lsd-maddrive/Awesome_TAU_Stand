#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#include <common.h>

#define CLOCKWISE_ROTATION  0
#define COUNTERCLOCKWISE_ROTATION 1

void pwmInitUp(void);

void pwmCheakingDirectionAndVoltage(uint8_t DirectionOfRotation, uint16_t Voltage);

void pwmStopEngine(void);


#endif /* INCLUDE_PWM_H_ */
