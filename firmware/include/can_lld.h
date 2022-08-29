#ifndef INCLUDE_CAN_LLD_H_
#define INCLUDE_CAN_LLD_H_

#include <common.h>

//Legs of the microcontroller (GPIOD 0 (RX) and GPIOD 1 (TX)) .
#define CAN1_RX_PIN PAL_LINE(GPIOD, 0)
#define CAN1_TX_PIN PAL_LINE(GPIOD, 1)

/*
 * @ brief  Writes the needed information to the device.
 *
 * @ note   Uses standard can function.
 *
 * @ param[in]  buf     Transferred configuration.
 */
msg_t canSimpleWrite(CANTxFrame *buf);

/*
 * @ brief  Reads the requested information from the device.
 *
 * @ note   Uses standard can function.
 *
 * @ param[in]  buf     A pointer to an array that contains the received data.
 */
msg_t canSimpleRead(CANRxFrame *buf);

/*
 * @brief   Launches can and sets microcontroller legs.
 *
 * @note    CAN1 is used.
 * @note    We use the GPIOD 0 (RX) and GPIOD 1 (TX) leg of the microcontroller.
 */
void canSimpleInit(void);

/*
 * @brief   Stops can if it's running.
 *
 * @note    CAN1 is used.
 */
void canSimpleUninit(void);


#endif /* INCLUDE_CAN_LLD_H_ */
