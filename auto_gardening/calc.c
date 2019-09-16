/*
 * calc.c
 *
 * Created: 2019-09-04 2:33:16 PM
 *  Author: ceehb
 */ 
 #include "calc.h"

int8_t calc_temp_sign(int16_t raw_temp_data)
{
	int8_t sign = 0;	// 1: negative, 0: positive, -1: error

	if((raw_temp_data & SIGN_MASK) == SIGN_MASK)
	{
		sign = 1;
	}
	else if((raw_temp_data & SIGN_MASK) == 0)
	{
		sign = 0;
	}
	else
	{
		sign = -1;			
	}

	return sign;
}

float calc_temp_value(int16_t raw_temp_data, int8_t* sign)
{
	float temperature = 0;	
	*sign = calc_temp_sign(raw_temp_data);

	if(*sign == 0)					// positive temperature value
	{
		temperature = (float)(((raw_temp_data << 5) >> 5) / 16.0);
	}
	else if(*sign == 1)				// negative temperature value
	{
		temperature = (float)(((((~(raw_temp_data)) + 0x0001) << 5) >> 5) / 16.0);	// 2's complement
	}
	else							// error
	{
		temperature = 9999.99;		
	}

	return temperature;
}

float calc_humi_level(uint16_t raw_humi_data)
{
	return (((float)(1023 - (raw_humi_data)) * HUM_PERCENT_MAX) / 1023 );
}

void calc_raw_data(int16_t raw_temp_data, int8_t* sign, float* temperature, uint16_t raw_humi_data, float* humidity)
{
	*temperature = calc_temp_value(raw_temp_data, sign);
	*humidity = calc_humi_level(raw_humi_data);
}
