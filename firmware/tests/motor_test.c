#include <motor_lld.h>


int16_t Voltage = 4000;//0...10000
bool flag = false;

void change_direction_of_rotation(void* args){
  (void)args;

  flag = false;
}

void test_motor(void) {
    halInit();
    chSysInit();
    motorSimpleInit();

    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, change_direction_of_rotation, NULL);
    while (true) {
      if (flag == true){
        motorSimpleStop();
        Voltage = -Voltage;
        flag = false;
      }
      else motorSetVoltage(Voltage);
      chThdSleepMilliseconds(200);
    }
}
