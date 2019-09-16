/*
 * read_sensor.c
 *
 * Created: 2019-09-03 5:09:10 PM
 *  Author: ceehb
 */ 
#include "config.h"
#include "read_sensor.h"
#include "ds18b20.h"
#include "bh1750.h"
#include "adc.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

void read_sensors(int16_t* raw_temp_data, uint16_t* raw_humi_data, uint16_t* raw_illum_data)
{
	read_temperature(raw_temp_data);
	read_humidity(raw_humi_data);
	read_light(raw_illum_data);
}

void read_temperature(int16_t* raw_temp_data)
{
	convert_ds18b20(&PORTB, &DDRB, &PINB, (1 << 1), NULL);

	_delay_ms(1000);

	read_ds18b20(&PORTB, &DDRB, &PINB, (1 << 1), NULL, raw_temp_data);
}

void read_humidity(uint16_t* raw_humi_data)
{
	*raw_humi_data = read_adc(0);
}

void read_light(uint16_t* raw_illum_data)
{
	read_bh1750_data(raw_illum_data);
}