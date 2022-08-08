#include "ch.h"
#include "hal.h"
#include <terminal_write.h>
#include "tests.h"
#include "stdlib.h"

//static const CANConfig cancfg= {
//CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
// CAN_BTR_SJW(0) | CAN_BTR_TS2(0) |
//CAN_BTR_TS1(5) | CAN_BTR_BRP(26)
//};


#define CAN1_RX_PIN PAL_LINE(GPIOD, 0)
#define CAN1_TX_PIN PAL_LINE(GPIOD, 1)

static uint32_t val;
float rotationspeed;
static CANDriver *can1 = &CAND1;

CANConfig conf = {
    .mcr = CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
    .btr = CAN_BTR_SJW(0) | CAN_BTR_TS2(2) | CAN_BTR_TS1(4) | CAN_BTR_BRP(11)
};

static CANRxFrame rxbuf;
static CANTxFrame txbuf;

/*0b100 - Data with EID or (0b110 - RemoteFrame with EID)*/
#define set_can_eid_data(x) ((x << 3)|0b100)

/*0b110 - Mask enable for EID/SID and DATA/RTR*/
#define set_can_eid_mask(x) ((x << 3)|0b110)


//static gazelParam gazel = {
//  .EngineSpeed = 0.0 ,
//  .DriverIsDemandEnginePercentTorque = 0,
//  .ActualEnginePercentTorque  = 0,
//  .Speed = 0.0,
//  .Speed_px4flow = 0.0,
//  .AcceleratorPedalPosition = 0,
//  .PercentLoadAtCurrentSpeed = 0,
//  .EngineFuelRate = 0 ,
//  .EngineInstantaneousFuelEconomy = 0 ,
//  .EngineThrottleValve = 0 ,
//  .BatteryPotential = 0 ,
//  .BrakePedalPosition=0
//};





void canUpdate(void){
      if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0){
        dbgPrintf("return\r\n");
        return;
      }
      while ( canReceive(&CAND1, CAN_ANY_MAILBOX, &rxbuf, TIME_IMMEDIATE) == MSG_OK)
            {

//              can_handler(rxbuf);
              dbgPrintf("%d\r\n", rxbuf);
            }
};



//void can_init ( void )
//{
//  //Setting pin mode
//    palSetPadMode(GPIOD,1,PAL_MODE_ALTERNATE(9));
//    palSetPadMode(GPIOD,0,PAL_MODE_ALTERNATE(9));
//
//  // Setting can filters
//
//    //Filters for can2 and can1 are configured together. See Reference manual( CAN filter master register (CAN_FMR) )
//    canSTM32SetFilters(&CAND1,8,0,NULL);
//
//    //start Can
//    canStart(&CAND1, NULL);
//    //chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);
//
//
//}





//gazelParam* gazelGetStruct(void){
//  return &gazel;
//};

void test(void){
  halInit();
  chSysInit();

  txbuf.RTR = CAN_RTR_DATA;
  txbuf.IDE = CAN_IDE_STD;
  txbuf.SID = 1;
  txbuf.DLC = 4;
  txbuf.data8[0] = 0x04;
  txbuf.data8[1] = 0x01;
  txbuf.data8[2] = 0x08;
  txbuf.data8[3] = 0x00;


  canStart(can1, &conf);
//  can1->State
//  (*)can1.State
  palSetLineMode(CAN1_RX_PIN, PAL_MODE_ALTERNATE(9));
  palSetLineMode(CAN1_TX_PIN, PAL_MODE_ALTERNATE(9));

  debugStreamInit();
  dbgPrintf("Start\r\n");
//  canTransmitTimeout(&CAND1, CAN_ANY_MAILBOX, &txbuf, TIME_MS2I(1000));

  while(true){

    canTransmitTimeout(&CAND1, CAN_ANY_MAILBOX, &txbuf, TIME_MS2I(1000));
    if(canReceiveTimeout(&CAND1, CAN_ANY_MAILBOX, &rxbuf, TIME_MS2I(1000)) ==MSG_OK){
      val = rxbuf.data8[6] << 24 | rxbuf.data8[5] << 16 | rxbuf.data8[4] << 8 | rxbuf.data8[3];
//      rotationspeed = val * 0.0183;
//      dbgPrintf("%.5f\r\n", rotationspeed);
      dbgPrintf("%d\r\n", val);

    }
    chThdSleepMilliseconds(500);
  }
}






