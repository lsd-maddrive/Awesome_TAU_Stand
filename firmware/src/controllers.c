#include "controllers.h"

contrstate_t contrstate = CONTR_UNINIT;
contrdata_t controldata = {
             .error={.current=0,
             .prev=0,
             .sum=0,
             .sum_lim=0,
             .prev_del=0,
             .current_del=0},
             .force={0,0,0}
};
controller_t contr = {
                      .type=NONE_CONTROL,
                      .sensor=NONE_SENS,
                      .settingContr={.coef={0}}
                      };


msg_t (*initControll)(controller_t*,sendata_t*,contrdata_t*);
msg_t (*activateControll)(controller_t*,sendata_t*,contrdata_t*);

contraction_t table_fun_contr[] = {
    [PID] = {pidInit,pidAct}
};

static THD_WORKING_AREA(thdcontrol, 256);
static THD_FUNCTION(control, arg)
{
  arg=arg;
  msg_t msg;
  sendata_t *sensdata;
  contrstate=CONTR_UNINIT;
  while(1){

    switch(contrstate)
    {
    case CONTR_UNINIT:
      if(contr.type != NONE_CONTROL && contr.sensor != NONE_SENS) contrstate = CONTR_INIT;
      break;
    case CONTR_INIT:
      getSensorsData(sensdata);
      msg = initControll(&contr,sensdata,&controldata);
      if(msg==MSG_OK)contrstate=CONTR_READY;
      break;

    case CONTR_READY:
      contrstate=CONTR_ACTIVE;
      break;

    case CONTR_ACTIVE:
      msg=activateControll(&contr,sensdata,&controldata);
      break;
    }
  }
}

void controllersStart(void)
{
    chThdCreateStatic(thdcontrol, sizeof(thdcontrol), NORMALPRIO, control, NULL);
}

void setNewControll(controller_t new_contr)
{
  contr=new_contr;
  contrstate=CONTR_INIT;
  initControll=table_fun_contr[contr.type].contr_initialize;
  activateControll=table_fun_contr[contr.type].contr_activate;
}
