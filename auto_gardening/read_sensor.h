/*
 * read_sensor.h
 *
 * Created: 2019-09-03 5:16:47 PM
 *  Author: ceehb
 */ 


#ifndef READ_SENSOR_H_
#define READ_SENSOR_H_

#include <inttypes.h>

void read_sensors(int16_t* temperature, uint16_t* humidity, uint16_t* lux);
void read_temperature(int16_t* temperature);
void read_humidity(uint16_t* humidity);
void read_light(uint16_t* lux);



#endif /* READ_SENSOR_H_ */