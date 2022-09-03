#include <pwm.h>


bool flag = false;

void change_direction_of_rotation(void* args){
  (void)args;
  flag = true;
}

void test_pwm(void) {
    halInit();
    chSysInit();
    pwmInitEngine();
    uint8_t DirectionOfRotation = CLOCKWISE_ROTATION;
    uint16_t Voltage = 4000;//0...10000
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, change_direction_of_rotation, NULL);
    while (true) {
      if (flag == true){
        pwmStopEngine();
        if (DirectionOfRotation == CLOCKWISE_ROTATION)DirectionOfRotation = COUNTERCLOCKWISE_ROTATION;
        else if (DirectionOfRotation == COUNTERCLOCKWISE_ROTATION)DirectionOfRotation = CLOCKWISE_ROTATION;
        flag = false;
      }
      else pwmSetEngineParams(DirectionOfRotation, Voltage);
      chThdSleepMilliseconds(200);
    }
}
