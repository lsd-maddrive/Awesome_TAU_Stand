#include <can_lld.h>

// @brief   Setting the can configuration
static const CANConfig can_conf = {
    .mcr = CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
    .btr = CAN_BTR_SJW(0) | CAN_BTR_TS2(2) | CAN_BTR_TS1(4) | CAN_BTR_BRP(11)
};

// Write a pointer to the bus in a variable
static CANDriver *can1 = &CAND1;

/*
 * @ brief  Writes the needed information to the device.
 *
 * @ note   Uses standard can function.
 *
 * @ param[in]  buf     Transferred configuration.
 */
msg_t canSimpleWrite(CANTxFrame *buf){
  return canTransmitTimeout(can1, CAN_ANY_MAILBOX, buf, TIME_MS2I(1000)) ;
}

/*
 * @ brief  Reads the requested information from the device.
 *
 * @ note   Uses standard can function.
 *
 * @ param[in]  buf     A pointer to an array that contains the received data.
 */
msg_t canSimpleRead(CANRxFrame *buf){
  return canReceiveTimeout(can1, CAN_ANY_MAILBOX, buf, TIME_MS2I(1000)) ;
}

/*
 * @brief   Launches can and sets microcontroller legs.
 *
 * @note    CAN1 is used.
 * @note    We use the GPIOD 0 (RX) and GPIOD 1 (TX) leg of the microcontroller.
 */
void canSimpleInit(void){
  palSetLineMode(CAN1_RX_PIN, PAL_MODE_ALTERNATE(9));
  palSetLineMode(CAN1_TX_PIN, PAL_MODE_ALTERNATE(9));

  canStart(can1, &can_conf);

}

/*
 * @brief   Stops can if it's running.
 *
 * @note    CAN1 is used.
 */
void canSimpleUninit(void){
  canStop(can1);
}
