#include <absolute_encoder.h>


static CANRxFrame rxbuf; // The result of reading from the device.
static CANTxFrame txbuf; // The transferred configuration.
static CANRxFrame buf; // Just for absolute_encoder_flush function (synchronizes the information read).

/*  @brief  Received characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation,
 *                           multi-turn angle of rotation.
 */
static absoluteEncoderParam absoluteEncoder = {
  .RotationalSpeed = 0.0 , // Rotation speed in rpm
  .NumberOfTurns = 0 , // Number of turns (can be both positive and negative).
  .AngleOfRotation = 0.0 , // Angle of rotation witin one turn (in range from 0 to 360 degrees).
  .MultiTurnAngleOfRotation = 0.0 , // Angle of rotation (greater or less than 0 degrees).
  .PreviousNumberOfTurns = 0 , // Number of turns in the previous count (Just for determining the direction of rotation).
  .PreviousAngleOfRotation = 0 // Angle of rotation witin one turn in the previous count (Just for determining the direction of rotation).
};

/*
 *  @brief  Completely clears the memory in which the read data is stored.
 *
 *  @note   Used to synchronize writing and reading information.
 *
 *  @notapi
 */
void absolute_encoder_flush(void){
  msg_t msg = MSG_TIMEOUT;
  while(msg != MSG_OK) {
    msg = canReceiveTimeout(&CAND1, CAN_ANY_MAILBOX, &buf, TIME_MS2I(1)) ;
  }
}

/*
 *  @brief  Measures encoder rotation speed in rpm.
 *
 *  @note   The reliability of the measurements was not checked.
 *
 *  @notapi
 */
void absolute_encoder_read_rotational_speed(void){
  txbuf.data8[2] = CAN_TXBUF_VELOCITY_BYTE; // Makes necessary configuration.
  uint8_t sign; // Direction of rotation.
  do{
    canSimpleWrite(&txbuf); // Writes configuration.
    // If the answer came, it will convert the data into the necessary ones.
    if(canSimpleRead(&rxbuf) == MSG_OK){
      // Checking for synchronization of sent and received data.
      if(rxbuf.data8[2] != CAN_TXBUF_VELOCITY_BYTE) absolute_encoder_flush(); // Synchronizes information.
      else break;
    }
    else palToggleLine(LINE_LED1);
  }while(1);
  absoluteEncoder.RotationalSpeed = (float)(rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3]) * COEF_VELOCITY;
  // Take into account direction of rotation.
  if (absoluteEncoder.NumberOfTurns == absoluteEncoder.PreviousNumberOfTurns){
    if (absoluteEncoder.AngleOfRotation - absoluteEncoder.PreviousAngleOfRotation >= 0) sign = CLOCKWISE_ROTATION;
    else sign = COUNTERCLOCKWISE_ROTATION;
  }
  else if (absoluteEncoder.NumberOfTurns - absoluteEncoder.PreviousNumberOfTurns > 0) sign = CLOCKWISE_ROTATION;
  else if (absoluteEncoder.NumberOfTurns - absoluteEncoder.PreviousNumberOfTurns < 0) sign = COUNTERCLOCKWISE_ROTATION;

  absoluteEncoder.RotationalSpeed = absoluteEncoder.RotationalSpeed * sign;
  absoluteEncoder.PreviousNumberOfTurns = absoluteEncoder.NumberOfTurns;
  absoluteEncoder.PreviousAngleOfRotation = absoluteEncoder.AngleOfRotation;
}

/*
 *  @brief  Measures number of turns from the starting position.
 *
 *  @note   The result can be both positive and negative, but it needs to be checked.
 *
 *  @notapi
 */
void absolute_encoder_read_number_of_turns(void){
  txbuf.data8[2] = CAN_TXBUF_TURNS_BYTE; // Makes necessary configuration.
  do{
    canSimpleWrite(&txbuf); // Writes configuration.
    // If the answer came, it will convert the data into the necessary ones.
    if(canSimpleRead(&rxbuf) ==MSG_OK){
      // Checking for synchronization of sent and received data.
      if(rxbuf.data8[2] != CAN_TXBUF_TURNS_BYTE) absolute_encoder_flush(); // Synchronizes information.
      else break;
    }
    else palToggleLine(LINE_LED1);
  }while(1);
  absoluteEncoder.NumberOfTurns = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
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
void absolute_encoder_read_angle_of_rotation(void){
  txbuf.data8[2] = CAN_TXBUF_ANGLE_BYTE; // Makes necessary configuration.
  do{
    canSimpleWrite(&txbuf); // Writes configuration.
    // If the answer came, it will convert the data into the necessary ones.
    if(canSimpleRead(&rxbuf) ==MSG_OK){
      // Checking for synchronization of sent and received data.
      if(rxbuf.data8[2] != CAN_TXBUF_ANGLE_BYTE) absolute_encoder_flush(); // Synchronizes information.
      else break;
    }
    else palToggleLine(LINE_LED1);
  }while(1);
  absoluteEncoder.AngleOfRotation = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
  absoluteEncoder.AngleOfRotation = absoluteEncoder.AngleOfRotation * COEF_ANGLE;
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
void absolute_encoder_calculate_multi_turn_angle_of_rotation(void){
  if (abs(absoluteEncoder.NumberOfTurns) < COEF_THRESHOLD_FOR_MULTI_TURN_ANGLE){ // Reads data from the encoder.
    txbuf.data8[2] = CAN_TXBUF_MULTI_TURN_ANGLE; // Makes necessary configuration.
    do{
      canSimpleWrite(&txbuf); // Writes configuration.
      // If the answer came, it will convert the data into the necessary ones.
      if(canSimpleRead(&rxbuf) ==MSG_OK){
        // Checking for synchronization of sent and received data.
        if(rxbuf.data8[2] != CAN_TXBUF_MULTI_TURN_ANGLE) absolute_encoder_flush(); // Synchronizes information.
        else break;
      }
      else palToggleLine(LINE_LED1);
    }while(1);
    absoluteEncoder.MultiTurnAngleOfRotation = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
    absoluteEncoder.MultiTurnAngleOfRotation = absoluteEncoder.MultiTurnAngleOfRotation * COEF_MULTI_TURN_ANGLE;
  }
  //Counts the angle of rotation, taking into account the sign in order to avoid overflow.
  else if(absoluteEncoder.NumberOfTurns >= COEF_THRESHOLD_FOR_MULTI_TURN_ANGLE)absoluteEncoder.MultiTurnAngleOfRotation = (absoluteEncoder.NumberOfTurns * 360) + absoluteEncoder.AngleOfRotation;
  else if(absoluteEncoder.NumberOfTurns <= -COEF_THRESHOLD_FOR_MULTI_TURN_ANGLE)absoluteEncoder.MultiTurnAngleOfRotation = 360 * absoluteEncoder.NumberOfTurns - (360 - absoluteEncoder.AngleOfRotation);
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
      absolute_encoder_read_number_of_turns(); // Measures the number of turns.
      absolute_encoder_read_rotational_speed(); // Measures encoder rotation speed.
      absolute_encoder_read_angle_of_rotation(); // Measures the rotation angle within one turn.
      absolute_encoder_calculate_multi_turn_angle_of_rotation(); // Measures the multi-turn rotation angle.

      if (chThdShouldTerminateX() == TRUE) break;
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( 50 ) );
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

  // Sets the the encoder mode (query).
  txbuf.DLC = CAN_TXBUF_DATA_LEN_4;
  txbuf.data8[0] = CAN_TXBUF_DATA_LEN_BYTE_4;
  txbuf.data8[1] = CAN_TXBUF_DEVICE_ID;
  txbuf.data8[2] = CAN_TXBUF_MODE;
  txbuf.data8[3] = CAN_TXBUF_QUERY_MODE;
  canSimpleWrite(&txbuf);

  // Starts another thread.
  chThdCreateStatic(waAbsoluteEncoder, sizeof(waAbsoluteEncoder), NORMALPRIO, absoluteEncoderThread, NULL);

}

/*
 *  @brief  Stops can (if it's enabled) and absolute encoder thread.
 *
 *  @param[out]    msg   A message is about if thread is stopped or not.
 *  @note   Not verified.
 */
msg_t absoluteEncoderUninit(void){
  chThdTerminate((thread_t *)absoluteEncoderThread);
  msg_t msg = chThdWait((thread_t *)absoluteEncoderThread);
  canSimpleUninit();
  return msg;
}

/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  absoluteEncoder.RotationalSpeed  Encoder rotation speed in rpm.
 */
float getAbsoluteEncoderRotationalSpeed(void){
  return absoluteEncoder.RotationalSpeed;
}

/*
 *  @brief  Returns number of turns from the starting position.
 *
 *  @param[out]  absoluteEncoder.NumberOfTurns  Number of turns  can be both positive
 *                                      and negative.
 *
 */
int32_t getAbsoluteEncoderNumberOfTurns(void){
  return absoluteEncoder.NumberOfTurns;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees within one turn.
 *
 *  @param[out]  absoluteEncoder.AngleOfRotation  The rotation angle can be in the range from 0 to 360 degrees.
 */
float getAbsoluteEncoderAngleOfRotation(void){
  return absoluteEncoder.AngleOfRotation;
}

/*
 *  @brief  Returns the rotation angle of the encoder in degrees.
 *
 *  @param[out]  absoluteEncoder.MultiTurnAngleOfRotation  The rotation angle can be greater or less than 0 degrees.
 */
int32_t getAbsoluteEncoderMultiTurnAngleOfRotation(void){
  return absoluteEncoder.MultiTurnAngleOfRotation;
}

/*
 *  @brief  Returns all characteristics from the encoder.
 *
 *  @param[out]  absoluteEncoder  Pointer to a structure where all characteristics are stored.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 */
absoluteEncoderParam* getAbsoluteEncoderStruct(void){
  return &absoluteEncoder;
};


