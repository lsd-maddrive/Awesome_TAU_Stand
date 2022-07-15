#ifndef INCLUDE_SENSOR_M3421_H_
#define INCLUDE_SENSOR_M3421_H_

#define SENSOR_M3421_ADDR 0b1101000

void sensor_m3421_init(void);
float get_volts(void);
void sensor_m3421_read(void);
void sensor_m3421_init(void);
uint8_t get_config(void);




#endif /* INCLUDE_SENSOR_M3421_H_ */
