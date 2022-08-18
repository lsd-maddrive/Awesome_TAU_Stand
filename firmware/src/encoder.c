#include <encoder.h>


static CANRxFrame rxbuf; // The result of reading from the device.
static CANTxFrame txbuf; // the transferred configuration.

/*  @brief  Received characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation,
 *                           multi-turn angle of rotation.
 */
static absoluteEncoderParam absoluteEncoder = {
  .RotationalSpeed = 0.0 , // Rotation speed in rpm
  .NumberOfTurns = 0.0 , // Number of turns (can be both positive and negative).
  .AngleOfRotation = 0.0 , // Angle of rotation witin one turn (in range from 0 to 360 degrees).
  .MultiTurnAngleOfRotation = 0.0 // Angle of rotation (greater or less than 0 degrees).
};

/*
 *  @brief  Measures encoder rotation speed in rpm.
 *
 *  @note   The reliability of the measurements was not checked.
 *
 *  @notapi
 */
void absoluteEncoderRotationalSpeed(void){
  txbuf.data8[2] = CAN_TXBUF_VELOCITY_BYTE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    absoluteEncoder.RotationalSpeed = (float)(rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3]) * COEF_VELOCITY;
    if (absoluteEncoder.NumberOfTurns < 0)absoluteEncoder.RotationalSpeed = -absoluteEncoder.RotationalSpeed;//Take into account the sign.
//    encoder.Speed = encoder.Speed * COEF_VELOCITY;
  }
  else palToggleLine(LINE_LED1);
}

/*
 *  @brief  Measures number of turns from the starting position.
 *
 *  @note   The result can be both positive and negative, but it needs to be checked.
 *
 *  @notapi
 */
void absoluteEncoderNumberOfTurns(void){
  absoluteEncoder.NumberOfTurns = (int32_t)absoluteEncoder.MultiTurnAngleOfRotation/360;
}

/*
 *  @brief  Measures the rotation angle of the encoder in degrees within one turn.
 *
 *  @note   The result is only positive.
 *  @note   The result can be in the range from 0 to 360 degrees.
 *
 *  @note   The reliability of the measurements was not checked.
 *
 *  @notapi
 */
void absoluteEncoderAngleOfRotation(void){
  txbuf.data8[2] = CAN_TXBUF_ANGLE_BYTE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    absoluteEncoder.AngleOfRotation = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
    absoluteEncoder.AngleOfRotation = absoluteEncoder.AngleOfRotation * COEF_ANGLE;
  }
  else palToggleLine(LINE_LED1);
}

/*
 *  @brief  Measures the rotation angle of the encoder in degrees.
 *
 *  @note   The result can be both positive and negative, but it needs to be checked.
 *  @note   The result can be greater or less than 0 degrees.
 *
 *  @note   The reliability of the measurements was not checked.
 *
 *  @notapi
 */
void absoluteEncoderMultiAngleOfRotation(void){
  txbuf.data8[2] = CAN_TXBUF_MULTI_TURN_ANGLE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    absoluteEncoder.MultiTurnAngleOfRotation = (int32_t)rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
  }
  else palToggleLine(LINE_LED1);
}

/*
 *  @brief  Starts another thread to read characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 *
 *  @notapi
 */
static THD_WORKING_AREA(waAbsoluteEncoder, 256);// 256 - stack size

static THD_FUNCTION(absoluteEncoderThread, arg)
{
    arg = arg; // just to avoid warnings

    systime_t time = chVTGetSystemTime();
    while( true ){
      absoluteEncoderMultiAngleOfRotation(); // Measures the multi-turn rotation angle.
      absoluteEncoderNumberOfTurns(); // Measures the number of turns.
      absoluteEncoderRotationalSpeed(); // Measures encoder rotation speed.
      absoluteEncoderAngleOfRotation(); // Measures the rotation angle within one turn.


      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( ENCODER_DATA_RATE ) );
    }
}

/*
 *  @brief  Initializes the encoder and starts another thread to read characteristics from it.
 *
 *  @note   Set encoder angular velocity sampling time (20 milliseconds).
 *  @note   Sets the zero position of the encoder.
 */
void absoluteEncoderInit(void){
  canSimpleInit(); // Launches can.

  // General encoder settings.
  txbuf.RTR = CAN_RTR_DATA; // Frame type (Data frame).
  txbuf.IDE = CAN_IDE_STD; // Identifier type (Standard id).
  txbuf.SID = CAN_SID; // Standard identifier.

  // Set encoder angular velocity sampling time (20 milliseconds).
  txbuf.DLC = CAN_TXBUF_DATA_LEN_5;
  txbuf.data8[0] = CAN_TXBUF_DATA_LEN_BYTE_5;
  txbuf.data8[1] = CAN_TXBUF_DEVICE_ID;
  txbuf.data8[2] = CAN_TXBUF_SET_SAMPLE_TIME;
  txbuf.data8[3] = CAN_TXBUF_SAMPLE_TIME;
  txbuf.data8[4] = CAN_TXBUF_ZERO_BYTE;
  canSimpleWrite(&txbuf);

  // Sets the zero position of the encoder.
  txbuf.DLC = CAN_TXBUF_DATA_LEN_4;
  txbuf.data8[0] = CAN_TXBUF_DATA_LEN_BYTE_4;
  txbuf.data8[1] = CAN_TXBUF_DEVICE_ID;
  txbuf.data8[2] = CAN_TXBUF_SET_ZERO_POSITION;
  txbuf.data8[3] = CAN_TXBUF_ZERO_BYTE;
  canSimpleWrite(&txbuf);

  // Sets the zero position of the encoder.
  txbuf.DLC = CAN_TXBUF_DATA_LEN_4;
  txbuf.data8[0] = CAN_TXBUF_DATA_LEN_BYTE_4;
  txbuf.data8[1] = CAN_TXBUF_DEVICE_ID;
  txbuf.data8[2] = CAN_TXBUF_MODE;
  txbuf.data8[3] = 0x00;
  canSimpleWrite(&txbuf);

  // Starts another thread.
  chThdCreateStatic(waAbsoluteEncoder, sizeof(waAbsoluteEncoder), NORMALPRIO, absoluteEncoderThread, NULL);

}

/*
 *  @brief  Stops can if it's enabled.
 *
 *  @note   Not verified.
 */
void absoluteEncoderUninit(void){
  canSimpleUninit();
}

/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  encoder.Speed  Encoder rotation speed in rpm.
 */
float getAbsoluteEncoderRotationalSpeed(void){
  return absoluteEncoder.RotationalSpeed;
}

/*
 *  @brief  Returns number of turns from the starting position.
 *
 *  @param[out]  encoder.NumberOfTurns  Number of turns  can be both positive
 *                                      and negative.
 *
 */
float getAbsoluteEncoderNumberOfTurns(void){
  return absoluteEncoder.NumberOfTurns;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees within one turn.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be in the range from 0 to 360 degrees.
 */
float getAbsoluteEncoderAngleOfRotation(void){
  return absoluteEncoder.AngleOfRotation;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be greater or less than 0 degrees.
 */
float getAbsoluteEncoderMultiTurnAngleOfRotation(void){
  return absoluteEncoder.MultiTurnAngleOfRotation;
}

/*
 *  @brief  Returns all characteristics from the encoder.
 *
 *  @param[out]  encoder  Pointer to a structure where all characteristics are stored.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 */
absoluteEncoderParam* getAbsoluteEncoderStruct(void){
  return &absoluteEncoder;
};




