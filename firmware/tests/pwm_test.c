#include <pwm.h>


// Сохраняем указатель на первый драйвер в переменную
static PWMDriver *pwm = &PWMD8;

void test_pwm(void) {
    halInit();
    chSysInit();
    pwmInit();
    while (true) {
        pwmCheakingDirectionAndVoltage(DirectionOfRotation, Voltage)
        chThdSleepMilliseconds(200);
    }
}
