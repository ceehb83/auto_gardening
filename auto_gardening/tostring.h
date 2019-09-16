/*
 * tostring.h
 *
 * Created: 2019-09-10 4:08:43 PM
 *  Author: ceehb
 */ 


#ifndef TOSTRING_H_
#define TOSTRING_H_

#include <inttypes.h>

void humi_to_string(float humidity, char* humidity_str);
void temp_to_string(int8_t sign, float temperature, char* temperature_str);
void integral_to_string(float data, char* integral_str);
void fractional_to_string(float data, char* fractional_str);
uint16_t ipow(uint16_t base, volatile uint8_t exponential);
void to_string(int8_t sign, float temperature, char* temperature_str, float humidity, char* humidity_str, uint16_t illumination, char* illumination_str);

#endif /* TOSTRING_H_ */