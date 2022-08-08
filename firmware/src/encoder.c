#include <encoder.h>


static CANRxFrame rxbuf; // The result of reading from the device.
static CANTxFrame txbuf; // the transferred configuration.

/*  @brief  Received characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation,
 *                           multi-turn angle of rotation.
 */
static encoderParam encoder = {
  .Speed = 0.0 , // Rotation speed in rpm
  .NumberOfTurns = 0.0 , // Number of turns (can be both positive and negative).
  .Angle = 0.0 , // Angle of rotation witin one turn (in range from 0 to 360 degrees).
  .MultiTurnAngle = 0.0 // Angle of rotation (greater or less than 0 degrees).
};

/*
 *  @brief  Measures encoder rotation speed in rpm.
 *
 *  @note   The reliability of the measurements was not checked.
 *
 *  @notapi
 */
void encoderVelocity(void){
  txbuf.data8[2] = CAN_TXBUF_VELOCITY_BYTE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    encoder.Speed = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
    encoder.Speed = encoder.Speed * COEF_VELOCITY;
  }
}

/*
 *  @brief  Measures number of turns from the starting position.
 *
 *  @note   The result can be both positive and negative, but it needs to be checked.
 *
 *  @notapi
 */
void encoderTurns(void){
  txbuf.data8[2] = CAN_TXBUF_TURNS_BYTE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    encoder.NumberOfTurns = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
  }
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
void encoderAngle(void){
  txbuf.data8[2] = CAN_TXBUF_ANGLE_BYTE; // Makes necessary configuration.
  canSimpleWrite(&txbuf); // Writes configuration.
  // If the answer came, it will convert the data into the necessary ones.
  if(canSimpleRead(&rxbuf) ==MSG_OK){
    encoder.Angle = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
    encoder.Angle = encoder.Angle * COEF_ANGLE;
  }
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
void encoderMultiAngle(void){
  if (encoder.NumberOfTurns > 0) encoder.MultiTurnAngle = (encoder.NumberOfTurns * 360) + encoder.Angle;
  else encoder.MultiTurnAngle = 360*(encoder.NumberOfTurns + 1) - (360 - encoder.Angle);;
}

/*
 *  @brief  Starts another thread to read characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 *
 *  @notapi
 */
static THD_WORKING_AREA(waEncoder, 256);// 256 - stack size

static THD_FUNCTION(encoderThread, arg)
{
    arg = arg; // just to avoid warnings

    systime_t time = chVTGetSystemTime();
    while( true ){
      encoderVelocity(); // Measures encoder rotation speed.
      encoderTurns(); // Measures the number of turns.
      encoderAngle(); // Measures the rotation angle within one turn.
      encoderMultiAngle(); // Measures the multi-turn rotation angle.

      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( ENCODER_DATA_RATE ) );
    }
}

/*
 *  @brief  Initializes the encoder and starts another thread to read characteristics from it.
 *
 *  @note   Set encoder angular velocity sampling time (20 milliseconds).
 *  @note   Sets the zero position of the encoder.
 */
void encoderInit(void){
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

  // Starts another thread.
  chThdCreateStatic(waEncoder, sizeof(waEncoder), NORMALPRIO, encoderThread, NULL);

}

/*
 *  @brief  Stops can if it's enabled.
 *
 *  @note   Not verified.
 */
void encoderUninit(void){
  canSimpleUninit();
}

/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  encoder.Speed  Encoder rotation speed in rpm.
 */
float getVelocity(void){
  return encoder.Speed;
}

/*
 *  @brief  Returns number of turns from the starting position.
 *
 *  @param[out]  encoder.NumberOfTurns  Number of turns  can be both positive
 *                                      and negative.
 *
 */
float getNumberOfTurns(void){
  return encoder.NumberOfTurns;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees within one turn.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be in the range from 0 to 360 degrees.
 */
float getAngle(void){
  return encoder.Angle;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be greater or less than 0 degrees.
 */
float getMultiTurnAngle(void){
  return encoder.MultiTurnAngle;
}

/*
 *  @brief  Returns all characteristics from the encoder.
 *
 *  @param[out]  encoder  Pointer to a structure where all characteristics are stored.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 */
encoderParam* encoderGetStruct(void){
  return &encoder;
};




