#include <scheduler.h>

stateDriver_t sdDriver={
                 .state=STATE_UNINIT,
                 .config={NONE_LOAD,0},
};

thread_t *tp_scheduler_sd;

extern mailbox_t main_mb;

static THD_WORKING_AREA(waStateDriver, 256);
static THD_FUNCTION(stateDriver, arg)
{
  arg=arg;

  msg_t received_msg;
  stateDriverInit(&sdDriver);
  while(1){
    msg_t msg_mb = chMBFetchTimeout(&main_mb, &received_msg, TIME_INFINITE);
    if(msg_mb==MSG_OK)
      {
        whatToDo(received_msg);
      }
  }
}

void schedulerStart(void)
{
  tp_scheduler_sd=chThdCreateStatic(waStateDriver, sizeof(waStateDriver), NORMALPRIO, stateDriver, NULL);
  chRegSetThreadName("scheduler");
}

void  whatToDo(msg_t received_msg)
{
  uint16_t address=0;
  int16_t value=0;
  float fullValue;
  address=received_msg;
  value=received_msg>>16;
  msg_t msg;
  dbgPrintf("address = %d  value = %d\r\n", address,value);
  if(address<100)//addresses of discrete registers : 0-99
  {
    switch (address) {
      case SYSTEM_STOP:
        if(value)
        {
          stateDriverDeactivateMotor(&sdDriver);
          stateDriverStop(&sdDriver);
          for(uint8_t i=1;i<REGISTER_LEN-1;i++)MB_WRITE_DISCRET_REG(i,FALSE);
        }
        MB_WRITE_DISCRET_REG(SYSTEM_STOP,value);
        break;

      case MEASURE:
        if(value){
            msg=stateDriverStart(&sdDriver);
            MB_WRITE_REG_INT16(DATA_CONTROL_TIME,CONTROL_TIME_DEFAULT);
          }
        else msg = stateDriverStop(&sdDriver);
        if(msg==MSG_OK)MB_WRITE_DISCRET_REG(MEASURE,value);
        break;

      case MOTOR:
        if(value)msg = stateDriverActivateMotor(&sdDriver);
        else msg = stateDriverDeactivateMotor(&sdDriver);
        if(msg==MSG_OK)MB_WRITE_DISCRET_REG(MOTOR,value);
        break;

      case FLAG_LOAD_1:
              if(!value || (setNewLoad(&sdDriver,FIRST_LOAD)!=MSG_OK)) value=FALSE;
              MB_WRITE_DISCRET_REG(FLAG_LOAD_1,value);
              if(value==TRUE)
              {
                MB_WRITE_DISCRET_REG(FLAG_LOAD_2,!value);
                MB_WRITE_DISCRET_REG(FLAG_LOAD_3,!value);

                for(uint8_t i=0;i<NUMBER_SENSORS;i++)
                {
                  if((sdDriver.config.load & (1<<i))!=0){
                      setNewSen(&sdDriver,i,SEN_ON);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,TRUE);
                    }
                  else{
                      setNewSen(&sdDriver,i,SEN_OFF);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,FALSE);
                    }
                }
              }
              break;
      case FLAG_LOAD_2:
              if(!value || (setNewLoad(&sdDriver,SECOND_LOAD)!=MSG_OK)) value=FALSE;
              MB_WRITE_DISCRET_REG(FLAG_LOAD_2,value);
              if(value==TRUE)
              {
                MB_WRITE_DISCRET_REG(FLAG_LOAD_1,!value);
                MB_WRITE_DISCRET_REG(FLAG_LOAD_3,!value);
                for(uint8_t i=0;i<NUMBER_SENSORS;i++)
                {
                  if((sdDriver.config.load & (1<<i))!=0){
                      setNewSen(&sdDriver,i,SEN_ON);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,TRUE);
                    }
                  else{
                      setNewSen(&sdDriver,i,SEN_OFF);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,FALSE);
                    }
                }
              }
              break;
      case FLAG_LOAD_3:
              if(!value || (setNewLoad(&sdDriver,THIRD_LOAD)!=MSG_OK)) value=FALSE;
              MB_WRITE_DISCRET_REG(FLAG_LOAD_3,value);
              if(value==TRUE)
              {
                MB_WRITE_DISCRET_REG(FLAG_LOAD_1,!value);
                MB_WRITE_DISCRET_REG(FLAG_LOAD_2,!value);
                for(uint8_t i=0;i<NUMBER_SENSORS;i++)
                {
                  if((sdDriver.config.load & (1<<i))!=0){
                      setNewSen(&sdDriver,i,SEN_ON);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,TRUE);
                    }
                  else{
                      setNewSen(&sdDriver,i,SEN_OFF);
                      MB_WRITE_DISCRET_REG(SENSORS_FIRST_FLAG+i,FALSE);
                    }
                }
              }
              break;

      case FLAG_CURRENT:
              if(setNewSen(&sdDriver,SEN_CURRENT,(senstep_t)value)==MSG_OK) MB_WRITE_DISCRET_REG(FLAG_CURRENT,value);
              break;
      case FLAG_ABS_ENCODER:
              if(setNewSen(&sdDriver,SEN_ABS_ENCODER,(senstep_t)value)==MSG_OK)MB_WRITE_DISCRET_REG(FLAG_ABS_ENCODER,value);
              break;
      case FLAG_INC_ENCODER:
              if(setNewSen(&sdDriver,SEN_INC_ENCODER,(senstep_t)value)==MSG_OK)MB_WRITE_DISCRET_REG(FLAG_INC_ENCODER,value);
              break;

      case FLAG_CONTROLLER_1:
             if(!value || (setNewControll(&sdDriver,MANUAL_CONTROL)!=MSG_OK)) value=FALSE;
             MB_WRITE_DISCRET_REG(FLAG_CONTROLLER_1,value);
             if(value==TRUE)MB_WRITE_DISCRET_REG(FLAG_CONTROLLER_2,!value);
             break;
      case FLAG_CONTROLLER_2:
             if(!value || (setNewControll(&sdDriver,SLAVE_CONTROL)!=MSG_OK)) value=FALSE;
             MB_WRITE_DISCRET_REG(FLAG_CONTROLLER_2,value);
             if(value==TRUE)MB_WRITE_DISCRET_REG(FLAG_CONTROLLER_1,!value);
             break;
      case FLAG_VARIABLE_SPEED:
             if(setNewParamControll(&sdDriver,VARIABLE_SPEED,(variablestep_t)value)==MSG_OK) MB_WRITE_DISCRET_REG(FLAG_VARIABLE_SPEED,value);
             break;
      case FLAG_VARIABLE_ANGLE:
             if(setNewParamControll(&sdDriver,VARIABLE_ANGLE,(variablestep_t)value)==MSG_OK) MB_WRITE_DISCRET_REG(FLAG_VARIABLE_ANGLE,value);
             break;
      case FLAG_VARIABLE_ROTATE:
             if(setNewParamControll(&sdDriver,VARIABLE_ROTATE,(variablestep_t)value)==MSG_OK) MB_WRITE_DISCRET_REG(FLAG_VARIABLE_ROTATE,value);
             break;
      case FLAG_VARIABLE_CURRENT:
             if(setNewParamControll(&sdDriver,VARIABLE_CURRENT,(variablestep_t)value)==MSG_OK) MB_WRITE_DISCRET_REG(FLAG_VARIABLE_CURRENT,value);
             break;
    }

  }
  else if(address>99)//addresses of analog registers : 0-99
  {
    switch(address-100)
    {
      case  DATA_MOTOR_REQUIRED_SPEED:
        if(setNewRequiredSpeed(&sdDriver,value)==MSG_OK)MB_WRITE_REG_INT16(DATA_MOTOR_REQUIRED_SPEED,value);
        break;
      case DATA_CONTR_KP:
        chMBFetchTimeout(&main_mb, &received_msg, TIME_INFINITE);
        fullValue=*(float*)&received_msg;
        if(fullValue>=0 && fullValue <=5)MB_WRITE_REG_FLOAT(DATA_CONTR_KP,fullValue);
        break;
      case DATA_CONTR_KI:
        chMBFetchTimeout(&main_mb, &received_msg, TIME_INFINITE);
        fullValue=*(float*)&received_msg;
        if(fullValue>=0 && fullValue <=5)MB_WRITE_REG_FLOAT(DATA_CONTR_KI,value);
        break;
      case DATA_CONTR_KD:
        chMBFetchTimeout(&main_mb, &received_msg, TIME_INFINITE);
        fullValue=*(float*)&received_msg;
        if(fullValue>=0 && fullValue <=5)MB_WRITE_REG_FLOAT(DATA_CONTR_KD,fullValue);
        break;
      case DATA_CONTROL_TIME:
        if(value>=5 && value<=500)MB_WRITE_REG_INT16(DATA_CONTROL_TIME,value);
        break;
    }

  }
}
