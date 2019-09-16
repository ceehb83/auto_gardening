/*
 * calc.h
 *
 * Created: 2019-09-04 2:33:58 PM
 *  Author: ceehb
 */ 


#ifndef CALC_H_
#define CALC_H_

#define SIGN_MASK				0xF800

#define HUM_PERCENT_MAX			100

#include <inttypes.h>

int8_t calc_temp_sign(int16_t raw_temp_data);
float calc_temp_value(int16_t raw_temp_data, int8_t* sign);
float calc_humi_level(uint16_t raw_humi_data);
void calc_raw_data(int16_t raw_temp_data, int8_t* sign, float* temperature, uint16_t raw_humi_data, float* humidity);

#endif /* CALC_H_ */