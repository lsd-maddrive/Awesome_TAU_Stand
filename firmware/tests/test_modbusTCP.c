#include "tests.h"
#include "modbusTCP.h"
#include "modbusRegister.h"

void test_modbusTCP(void)
{
  	chSysInit();
  	halInit();
	modbustcp_init();
	for(uint8_t i=0;i<100;i++)
	{
		Analog_Register[i]=i*100+100;	
		Discrete_Register[i]=i % 2;
	}
	modbustcp_start();
	while(true)
	{
		chThdSleepMilliseconds(1000);
		palToggleLine(LINE_LED2);
	}	
} 