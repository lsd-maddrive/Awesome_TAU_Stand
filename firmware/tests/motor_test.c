#include <motor_control.h>
#include <terminal_write.h>


int16_t Voltage = -5000;//0...10000
bool flag = false;

void change_direction_of_rotation(void* args){
  (void)args;

  flag = true;
}

void test_motor(void) {
    halInit();
    chSysInit();
    motorInit();
    debugStreamInit();
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, change_direction_of_rotation, NULL);
    while (true) {

      if (flag == true){
        Voltage = -Voltage;
        setMotorVoltage(Voltage);
        flag = false;
      }
      palToggleLine(LINE_LED2);
      dbgPrintf("Currnet voltage:%d\r\n", getMotorCurrentVoltage());
      chThdSleepMilliseconds(200);
    }
}
