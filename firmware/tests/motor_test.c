#include <motor_lld.h>


bool flag = false;

void change_direction_of_rotation(void* args){
  (void)args;
  flag = true;
}

void test_motor(void) {
    halInit();
    chSysInit();
    motorSimpleInit();
    uint8_t DirectionOfRotation = CLOCKWISE_ROTATION;
    uint16_t Voltage = 4000;//0...10000
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, change_direction_of_rotation, NULL);
    while (true) {
      if (flag == true){
        motorSimpleStop();
        if (DirectionOfRotation == CLOCKWISE_ROTATION)DirectionOfRotation = COUNTERCLOCKWISE_ROTATION;
        else if (DirectionOfRotation == COUNTERCLOCKWISE_ROTATION)DirectionOfRotation = CLOCKWISE_ROTATION;
        flag = false;
      }
      else motorSetVoltage(DirectionOfRotation, Voltage);
      chThdSleepMilliseconds(200);
    }
}
