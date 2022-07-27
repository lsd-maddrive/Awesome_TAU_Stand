#include "measurements.h"

senstate_t senstate = SEN_UNINIT;
load_t load = NONE_LOAD;

msg_t (*initSensors)(sendata_t*);
msg_t (*activateSensors)(sendata_t*);


senaction_t table_fun_sen[] = {
    [NONE_LOAD] = {noneLoadInit,noneLoadAct},
    [FIRST_LOAD] = {firstLoadInit,firstLoadAct},
    [SECOND_LOAD]={secondLoadInit,secondLoadAct},
    [THIRD_LOAD]={thirdLoadInit,thirdLoadAct},
};

sendata_t table_data[] = {
    [SEN_CURRENT] = {SEN_OFF,NO_ERROR,{0,0}},
    [SEN_ENCODER] = {SEN_OFF,NO_ERROR,{0,0}},
};

static THD_WORKING_AREA(sensors, 256);
static THD_FUNCTION(SensContr, arg)
{
  arg=arg;
  msg_t msg;
  senstate=SEN_UNINIT;
  while(1){

    switch(senstate)
    {
    case SEN_UNINIT:
      if(load != NONE_LOAD) senstate = SEN_INIT;
      break;
    case SEN_INIT:
      msg = initSensors(table_data);
      if(msg==MSG_OK)senstate=SEN_READY;
      break;

    case SEN_READY:
      senstate=SEN_ACTIVE;
      break;

    case SEN_ACTIVE:
      msg=activateSensors(table_data);
      break;

    }
  }
}

void measurementsStart(void)
{
    chThdCreateStatic(sensors, sizeof(sensors), NORMALPRIO, SensContr, NULL);
}

void setNewLoad(load_t new_load)
{
  load=new_load;
  senstate=SEN_INIT;
  initSensors=table_fun_sen[load].sen_initialize;
  activateSensors=table_fun_sen[load].sen_activate;
}

void getSensorsData(sendata_t* sendata)
{
  sendata=table_data;
  sendata[SEN_CURRENT].measur.current=0;
}



