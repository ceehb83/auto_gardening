/*
 * auto_gardening.c
 *
 * Created: 2019-09-03 1:26:33 PM
 * Author : ceehb
 */

#include "config.h"
#include "read_sensor.h"
#include "calc.h"
#include "tostring.h"
#include "usart.h"
#include "timer.h"
#include "twowire.h"
#include "adc.h"
#include "bh1750.h"
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

void init_port()
{
	//DDRB |= (1 << PORTB0);
	
	/* PORTB1 - Temperature DQ pin 1-wire - in & out */
	DDRB &= ~(1 << PORTB1);

	/* PORTB3 - Fan output */
	DDRB |= (1 << PORTB3);

	/* PORTB4 - Valve output */
	DDRB |= (1 << PORTB4);

	/* PORTB5 - LED output */
	DDRB |= (1 << PORTB5);
}

void initialization(void)
{
	init_port();
	init_timer1();
	init_twowire();
	_delay_us(10);
	init_usart();
	init_adc();
	init_bh1750();
}

int main(void)
{
	int8_t temp_sign = 0;
	int16_t raw_temp_data = 0;
	float temperature = 0;

	uint16_t raw_humi_data = 0;
	float humidity = 0;

	uint16_t illumination = 0;

	char humidity_str[7] = {0};	
	char temperature_str[12] = {0};
	char illumination_str[7] = {0};

	initialization();
	_delay_ms(1000);

	put_string_usart("\n\ninitialization completed\n\n");

    /* Replace with your application code */
    while (1) 
    {
		read_sensors(&raw_temp_data, &raw_humi_data, &illumination);
		calc_raw_data(raw_temp_data, &temp_sign, &temperature, raw_humi_data, &humidity);
		to_string(temp_sign, temperature, temperature_str, humidity, humidity_str, illumination, illumination_str);

		put_string_usart("test temperature: \t");
		put_string_usart(temperature_str);
		put_string_usart(" degC\n");

		put_string_usart("test humidity: \t\t");
		put_string_usart(humidity_str);
		put_string_usart(" %\n");

		put_string_usart("test light-intensity: \t");
		put_string_usart(illumination_str);
		put_string_usart(" lux\n\n");
    }
}

