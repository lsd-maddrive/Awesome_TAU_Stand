#include <common.h>


static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == I2C_TEST)
    test_i2c();
#elif(PROGRAM_ROUTINE == SENSOR_M3421_TEST)
    test_sensor_m3421();
#elif(PROGRAM_ROUTINE == CURRENT_SENSOR_TEST)
    test_current_sensor();
#elif(PROGRAM_ROUTINE == CAN_TEST)
    test_can();
#elif(PROGRAM_ROUTINE == MODBUSTCP_TEST)
    test_modbusTCP();
#elif(PROGRAM_ROUTINE == INTERRUPT_WITH_TIMER_TEST)
    test_interrupt();
#endif
#elif(PROGRAM_ROUTINE == MOTOR_TEST)
    test_motor();
#elif(PROGRAM_ROUTINE == STATE_DRIVER_TEST)
    test_sd();
#endif
}



int main(void) {
#if(PROGRAM_ROUTINE != MAIN_ROUTINE)
    testRoutines();

#else
    chSysInit();
    halInit();

    while(1);

#endif
}
