#include <common.h>

static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == FIRST_TEST)
    first_test();
#elif(PROGRAM_ROUTINE == I2C_TEST)
    test_i2c();
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
