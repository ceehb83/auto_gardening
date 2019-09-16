/*
 * adc.c
 *
 * Created: 2019-09-03 2:19:28 PM
 *  Author: ceehb
 */ 

 #include "adc.h"
 #include <avr/io.h>

 void init_adc(void)
 {
	// ADMUX
	/**/

	ADMUX |= (1 << REFS0);

	//ADCSRA
	/**/
	ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
 }

 uint16_t read_adc(uint8_t channel)
 {
	ADMUX &= 0xF0;
	ADMUX |= channel;
	ADCSRA |= (1 << ADSC);			// Starts a new conversion
									// wait until the conversion is done
	while(ADCSRA & (1 << ADSC));	// ADSC:0 - complete, 1: in progress 

	return ADCW;					// Return the ADC value of the chosen channel
 }