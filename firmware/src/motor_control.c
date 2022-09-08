#include <motor_control.h>

static uint8_t NewDirectionOfRotation = CLOCKWISE_ROTATION;
static uint16_t NewVoltage = 5000; // 5000 - 50%
static uint8_t PresentDirectionOfRotation = CLOCKWISE_ROTATION;
static uint16_t PresentVoltage = 7000; // 7000 - 70%
static bool MotorState = true


void update_motor_voltage(void){
  if ((NewVoltage - PresentVoltage) > 100){
    PresentVoltage += 100;
    motorSetVoltage(PresentDirectionOfRotation, PresentVoltage);
  }
  else if ((NewVoltage - PresentVoltage) < -100){
    PresentVoltage -= 100;
    motorSetVoltage(PresentDirectionOfRotation, PresentVoltage);

  }
  else if ((NewVoltage - PresentVoltage) != 0){
    PresentVoltage += (NewVoltage - PresentVoltage);
    motorSetVoltage(PresentDirectionOfRotation, PresentVoltage);
  }
}

void check_direction_of_rotation(void){
  if (NewDirectionOfRotation != PresentDirectionOfRotation){
    motorSimpleStop();
    chThdSleepMilliseconds(1000);

    PresentVoltage = 0;
    PresentDirectionOfRotation = NewDirectionOfRotation;
  }
}

static THD_WORKING_AREA(waMotor, 256);// 256 - stack size

static THD_FUNCTION(motorThread, arg)
{
    arg = arg; // just to avoid warnings
    systime_t time = chVTGetSystemTime();
    while( true ){
      if (MotorState == true){
        check_direction_of_rotation();
        update_motor_voltage();
      }
      else motorSimpleStop();
      if (chThdShouldTerminateX() == TRUE) chThdExit(MSG_OK);
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( 20 ) );
    }
}

void motorInit(void){
  motorSimpleInit();
  chThdCreateStatic(waMotor, sizeof(waMotor), NORMALPRIO, motorThread, NULL);
}

msg_t motorUninit(void){
  chThdTerminate((thread_t *)motorThread);
  msg_t msg = chThdWait((thread_t *)motorThread);
  motorSimpleUninit();
  return msg;
}
