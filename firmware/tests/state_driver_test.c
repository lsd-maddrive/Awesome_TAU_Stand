#include <common.h>
#include <tests.h>

#include "state_driver.h"


DConfig sdConf = {
         .load=FIRST_LOAD,

};

Driver sdDriver={0};


void sd_test(void){
  halInit();
  chSysInit();


  stateDriverInit(&sdDriver);
  stateDriverStart(&sdDriver,&sdConf);
  stateDriverActivate(&sdDriver);

    while (1)
    {

    }
}
