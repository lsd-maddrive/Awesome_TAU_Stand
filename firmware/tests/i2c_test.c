#include "common.h"
#include "lld_i2c.h"
#include <hal.h>
#include <ch.h>


static const SerialConfig sd_st_cfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};

static SerialDriver         *debug_serial = &SD3;
static BaseSequentialStream *debug_stream = NULL;

static void debug_stream_init( void )
{
    sdStart( debug_serial, &sd_st_cfg );
    palSetPadMode( GPIOD, 8, PAL_MODE_ALTERNATE(7) );
    palSetPadMode( GPIOD, 9, PAL_MODE_ALTERNATE(7) );

    debug_stream = (BaseSequentialStream *)debug_serial;
}

static void dbgprintf( const char* format, ... )
{
    if ( !debug_stream )
        return;

    va_list ap;
    va_start(ap, format);
    chvprintf(debug_stream, format, ap);
    va_end(ap);
}


void test_i2c(void){
  chSysInit();
  halInit();
  debug_stream_init();
  i2cStartUp();

  uint8_t txbuf[5] = {0xA0, 0x0F, 0x00, 0x01, 0x30};
  uint8_t rxbuf[6] = {0};
  uint8_t data_reg = 0b10101000;
  i2cSimpleWrite(0b1101010, txbuf, 5);
  dbgprintf("start\r\n");

  while(true){
    i2cRegisterRead(0b1101010, data_reg, rxbuf, 6);
    int16_t* temp = (int16_t*)rxbuf;
    dbgprintf("x %d, y %d, z %d\r\n", temp[0], temp[1], temp[2]);
    dbgprintf("%d %d %d\r\n", b[0], i2cGetErrors(&I2CD1), msg);

    chThdSleepMilliseconds(1000);
  }
}
