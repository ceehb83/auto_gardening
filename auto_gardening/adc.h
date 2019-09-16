/*
 * adc.h
 *
 * Created: 2019-09-03 2:25:02 PM
 *  Author: ceehb
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "config.h"
#include <inttypes.h>

void init_adc(void);
uint16_t read_adc(uint8_t channel);

#endif /* ADC_H_ */