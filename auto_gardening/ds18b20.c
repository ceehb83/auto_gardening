/*
 * ds18b20.c
 *
 * Created: 2019-09-03 4:38:40 PM
 *  Author: ceehb
 */ 
#include "ds18b20.h"
#include "onewire.h"
#include "usart.h"
#include <stdlib.h>
#include <stdio.h>

uint8_t read_ds18b20_scratchpad(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom, uint8_t* sp)
{
	uint8_t i = 0;

	// comm check
	if(init_onewire(port, direction, port_in, mask) == ONEWIRE_COMM_ERR)
	{
		return DS18B20_ERROR_COMM;
	}

	// match rom
	match_ds18b20(port, direction, port_in, mask, rom);

	// read scratch pad
	write_onewire(port, direction, port_in, mask, DS18B20_COMMAND_READ_SP);
	for(i = 0; i < 9; i++)
	{
		sp[i] = read_onewire(port, direction, port_in, mask);
	}

	// check pull up
	if((sp[0] | sp[1] | sp[2] | sp[3] | sp[4] | sp[5] | sp[6] | sp[7]) == 0)
	{
		return DS18B20_ERROR_PULL;
	}

	return DS18B20_ERROR_OK;
}

uint8_t read_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom, int16_t* temperature)
{
	uint8_t sp[9];
	uint8_t err_code = 0;

	err_code = read_ds18b20_scratchpad(port, direction, port_in, mask, rom, sp);

	if(err_code != DS18B20_ERROR_OK)
	{
		put_string_usart("ds18b20 error\n");
		*temperature = 0;
		return err_code;
	}

	*temperature = (int16_t)(sp[1] << 8) + sp[0];
	// lsb = sp[0], msb = sp[1]

	return DS18B20_ERROR_OK;
}

void match_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom)
{
	uint8_t i = 0;

	if(rom == NULL)
	{
		// Skip ROM
		write_onewire(port, direction, port_in, mask, DS18B20_COMMAND_SKIP_ROM);
	}
	else
	{
		// Match ROM
		write_onewire(port, direction, port_in, mask, DS18B20_COMMAND_MATCH_ROM);
		for(i = 1; i < 8; i++)
		{
			write_onewire(port, direction, port_in, mask, rom[i]);
		}
	}
}

uint8_t convert_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom)
{
	// comm check
	if(init_onewire(port, direction, port_in, mask) == ONEWIRE_COMM_ERR)
	{
		return DS18B20_ERROR_COMM;
	}
	// rom match
	match_ds18b20(port, direction, port_in, mask, rom);

	// convert temperature
	write_onewire(port, direction, port_in, mask, DS18B20_COMMAND_CONVERT);

	return DS18B20_ERROR_OK;	
}