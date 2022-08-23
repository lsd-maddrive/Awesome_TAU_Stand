#include <can_lld.h>

/* @brief   Setting the can configuration
 *
 * @note    mcr (master control register):
 *          CAN_MCR_ABOM (Automatic bus-off management): This bit controls the behavior of the CAN hardware
 *                                                       on leaving the Bus-Off state.
 *
 *          CAN_MCR_AWUM (Automatic wakeup mode): This bit controls the behavior of the CAN hardware on message
 *                                                reception during Sleep mode.
 *
 *          CAN_MCR_TXFP (Transmit FIFO priority): This bit controls the transmission order when several mailboxes
 *                                                 are pending at the same time.
 *
 * @note    btr (bit timing register):
 *          CAN_BTR_SJW (Resynchronization jump width): These bits define the maximum number of time quanta the CAN
 *                                                      hardware is allowed tolengthen or shorten a bit to perform
 *                                                      the resynchronization.
 *                                                      tRJW = tq x (SJW[1:0] + 1)
 *
 *          CAN_BTR_TS2 (Time segment 2): These bits define the number of time quanta in Time Segment 2
 *                                        tBS2 = tq x (TS2[2:0] + 1)
 *
 *          CAN_BTR_TS1 (Time segment 1): These bits define the number of time quanta in Time Segment 1
 *                                        tBS1 = tq x (TS1[3:0] + 1)
 *
 *          CAN_BTR_BRP (Baud rate prescaler): These bits define the length of a time quanta.
 *                                             tq = (BRP[9:0]+1) x tPCLK
 *
 * @note    tq = (BRP[9:0] + 1) x tPCLK;
 *          tPCLK = time period of the APB clock
 */
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
