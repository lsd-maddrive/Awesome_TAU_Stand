#include <motor_control.h>
#include <terminal_write.h>


int16_t Voltage = 5000;//0...10000
bool flag = false;

void change_direction_of_rotation(void* args){
  (void)args;

  flag = true;
}

void test_motor(void) {
    halInit();
    chSysInit();
    motorInit();

    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, change_direction_of_rotation, NULL);
    setMotorVoltage(Voltage);
    while (true) {
      palToggleLine(LINE_LED2);
      if (flag == true){
        motorSimpleStop();
        Voltage = -Voltage;
        setMotorVoltage(Voltage);
        flag = false;
      }
      dbgPrintf("Currnet voltage: %d", getMotorCurrentVoltage());
      chThdSleepMilliseconds(200);
    }
}
