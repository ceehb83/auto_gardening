/*
 * tostring.c
 *
 * Created: 2019-09-10 3:54:10 PM
 *  Author: ceehb
 */ 
#include "tostring.h"
#include <string.h>
#include <stdlib.h>

void illum_to_string(uint16_t illumination, char* illumination_str)
{
	memset(illumination_str, 0, strlen(illumination_str));
	integral_to_string(illumination, illumination_str);
}

void humi_to_string(float humidity, char* humidity_str)
{
	char integralStr[3] = {0};
	char fractionalStr[4] = {0};
	memset(humidity_str, 0, strlen(humidity_str));

	integral_to_string(humidity, integralStr);
	fractional_to_string(humidity, fractionalStr);

	strcat(humidity_str, integralStr);
	strcat(humidity_str, fractionalStr);
}

void temp_to_string(int8_t sign, float temperature, char* temperature_str)
{
	char integralStr[5] = {0};
	char fractionalStr[4] = {0};
	memset(temperature_str, 0, strlen(temperature_str));

	if(sign == 1)
	{
		strcat(temperature_str, "-");
	}
	else
	{
		;
	}

	integral_to_string(temperature, integralStr);
	fractional_to_string(temperature, fractionalStr);

	strcat(temperature_str, integralStr);
	strcat(temperature_str, fractionalStr);
}

void integral_to_string(float data, char* integral_str)
{
	itoa((int16_t)(data), integral_str, 10);
}

uint16_t ipow(uint16_t base, volatile uint8_t exponential)
{
	uint16_t result = 1;

	while(exponential > 0)
	{
		if(exponential & 1)
		{
			result *= base;
		}
		base *= base;
		exponential >>= 1;
	}

	return result;
}

void fractional_to_string(float data, char* fractional_str)
{
	uint8_t tmp = 0;
	uint16_t fraction = (data - (int16_t)(data)) * 100;

	*fractional_str++ = '.';

	tmp = (uint8_t)(fraction / ipow(10, 1));
	*fractional_str++ = 48+tmp;
	fraction = (fraction % ipow(10, 1));

	tmp = (uint8_t)(fraction / ipow(10, 0));
	*fractional_str++ = 48+tmp;
	fraction = (fraction % ipow(10, 0));

	*fractional_str = '\0';
}

void to_string(int8_t sign, float temperature, char* temperature_str, float humidity, char* humidity_str, uint16_t illumination, char* illumination_str)
{
	temp_to_string(sign, temperature, temperature_str);
	humi_to_string(humidity, humidity_str);
	illum_to_string(illumination, illumination_str);
}