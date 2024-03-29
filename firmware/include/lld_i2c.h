#ifndef INCLUDE_LLD_I2C_H_
#define INCLUDE_LLD_I2C_H_

#include <common.h>

/*
 * @brief   Launches I2C and sets microcontroller legs.
 *
 * @note    I2c1 is used.
 * @note    We use the GPIOB 8 (SCL) and GPIOB 9 (SDA) leg of the microcontroller.
 */
void i2cStartUp(void);

/*
 * @brief   Stops I2C if it's running.
 *
 * @note    I2c1 is used.
 */
void i2cSimpleStop(void);

/*
 * @ brief  Writes the needed information to the device.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              buf     Register address containing the data to be passed.
 *              n       Number of bytes to send.
 */
msg_t i2cSimpleWrite(uint8_t addr, uint8_t *buf, uint8_t n);

/*
 * @ brief  Reads the requested information from the device.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              buf     A pointer to an array that contains the received data.
 *              n       Number of bytes to read.
 */
msg_t i2cSimpleRead(uint8_t addr, uint8_t *buf, uint8_t n);

/*
 * @ brief  Writes to a device and reads from the device the
 *          requested information.
 *
 * @ note   Uses standard i2c function.
 *
 * @ param[in]  addr    7 bit slave address.
 *              raddr   8 bit register address.
 *              buf     A pointer to an array that contains the received data.
 *              n       Number of bytes to read.
 */
msg_t i2cRegisterRead(uint8_t addr, uint8_t raddr, uint8_t *buf, uint8_t n);



#endif /* INCLUDE_LLD_I2C_H_ */
