#include <common.h>
#include <can_lld.h>

#ifndef INCLUDE_ENCODER_H_
#define INCLUDE_ENCODER_H_

// Coefficients for counting measurements.
#define COEF_VELOCITY 2.9296875 // Coef for encoder rotation speed. [60 / (1024 * 20 * 0.001)]
                                // 20 * 0.001 is 20 milliseconds.
#define COEF_ANGLE 0.3515625 // Coef for angle of rotation witin one turn. [360/1024]

#define CAN_SID 1 // ???

// Data length.
#define CAN_TXBUF_DATA_LEN_5 5
#define CAN_TXBUF_DATA_LEN_4 4

// Command FUNC.
#define CAN_TXBUF_ANGLE_BYTE 0x01
#define CAN_TXBUF_SET_ZERO_POSITION 0x06
#define CAN_TXBUF_TURNS_BYTE 0x09
#define CAN_TXBUF_VELOCITY_BYTE 0x0A
#define CAN_TXBUF_SET_SAMPLE_TIME 0x0B

// Data length.
#define CAN_TXBUF_DATA_LEN_BYTE_5 0x05
#define CAN_TXBUF_DATA_LEN_BYTE_4 0x04

#define CAN_TXBUF_DEVICE_ID 0x01
#define CAN_TXBUF_SAMPLE_TIME 0x14 // 20 milliseconds.
#define CAN_TXBUF_ZERO_BYTE 0x00
#define ENCODER_DATA_RATE 20 // Data rate is 50. [1/50 is 20 milliseconds].


/*  @brief  Received characteristics from the encoder.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation,
 *                           multi-turn angle of rotation.
 */
typedef struct
{
    float Speed ; // Rotation speed in rpm
    int32_t NumberOfTurns; // Number of turns (can be both positive and negative).
    float Angle; // Angle of rotation witin one turn (in range from 0 to 360 degrees).
    float MultiTurnAngle; // Angle of rotation (greater or less than 0 degrees).
} encoderParam;

/*
 *  @brief  Initializes the encoder and starts another thread to read characteristics from it.
 *
 *  @note   Set encoder angular velocity sampling time (20 milliseconds).
 *  @note   Sets the zero position of the encoder.
 */
void encoderInit(void);

/*
 *  @brief  Stops can if it's enabled.
 *
 *  @note   Not verified.
 */
void encoderUninit(void);


/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  encoder.Speed  Encoder rotation speed in rpm.
 */
float getVelocity(void);

/*
 *  @brief  Returns number of turns from the starting position.
 *
 *  @param[out]  encoder.NumberOfTurns  Number of turns  can be both positive
 *                                      and negative.
 *
 */
float getNumberOfTurns(void);

/*
 *  @brief  Returns the rotation angle of the encoder in degrees within one turn.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be in the range from 0 to 360 degrees.
 */
float getAngle(void);

/*
 *  @brief  Returns the rotation angle of the encoder in degrees.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be greater or less than 0 degrees.
 */
float getMultiTurnAngle(void);

/*
 *  @brief  Returns all characteristics from the encoder.
 *
 *  @param[out]  encoder  Pointer to a structure where all characteristics are stored.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 */
encoderParam* encoderGetStruct(void);


#endif /* INCLUDE_ENCODER_H_ */
