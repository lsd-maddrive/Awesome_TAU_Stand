#include "lld_i2c.h"

/* @brief   Setting the driver configuration
 *
 * @note    Clock frequency i2c 54 MHz
 */
static const I2CConfig i2c1_conf = {
    .timingr = STM32_TIMINGR_PRESC(14U)  |
    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
    .cr1 = 0,
    .cr2 = 0
};

// Write a pointer to the driver in a variable
static I2CDriver* i2c1 =  &I2CD1;

/*
 * @brief   Launches I2C and sets microcontroller legs.
 *
 * @note    I2c1 is used.
 * @note    We use the GPIOB 8 (SLC) and GPIOB 9 (SDA) leg of the microcontroller.
 */
void i2cStartUp(void){
  i2cStart(i2c1, &i2c1_conf);
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(4) |
                        PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                        PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(4) |
                        PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                        PAL_STM32_PUPDR_PULLUP);
}

/*
 * @ brief  Writes the needed information to the device.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              buf     Register address containing the data to be passed.
 *              n       Number of bytes to send.
 */
msg_t i2cSimpleWrite(uint8_t addr, uint8_t *buf, uint8_t n){
  return i2cMasterTransmitTimeout(i2c1, addr, buf, n, NULL, 0, 1000);
}

/*
 * @ brief  Reads the requested information from the device.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              buf     A pointer to an array that contains the received data.
 *              n       Number of bytes to read.
 */
msg_t i2cSimpleRead(uint8_t addr, uint8_t *buf, uint8_t n){
 return i2cMasterReceive(i2c1, addr, buf, n);
}

/*
 * @ brief  Writes to a device and reads from the device the
 *          requested information.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              raddr   Pointer to an array containing the data to be passed.
 *              buf     A pointer to an array that contains the received data.
 *              n       Number of bytes to read.
 */
msg_t i2cRegisterRead(uint8_t addr, uint8_t raddr, uint8_t *buf, uint8_t n){
 return i2cMasterTransmit(i2c1, addr, &raddr, 1, buf, n);
}

