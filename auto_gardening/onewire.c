/*
 * onewire.c
 *
 * Created: 2019-09-03 3:06:50 PM
 *  Author: ceehb
 */ 
#include "config.h"
#include "onewire.h"
#include <util/delay.h>

uint8_t init_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask)
{
	uint8_t response = 0;

	*direction |= mask;				// port output
	*port |= mask;					// write 1
	*port &= ~mask;					// write 0 - pull the bus low

	_delay_us(600);			

	*direction &= ~mask;			// set port to input - Master goes into receive mode
	
	_delay_us(70);					// rising edge and waits 15-60us device tx a presence pulse by pulling the bus low
									// 500 + 70 -> for a minimum of 480us	
	response = *port_in & mask;		// 0: comm ok, 1: comm error

	_delay_us(200);					// presence pulse 60 - 240us
	_delay_us(300);

	return response != 0? ONEWIRE_COMM_ERR : ONEWIRE_COMM_OK;	// 0: comm ok, 1: comm error
}

uint8_t write_bit_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t bit)
{
	*direction |= mask;
	*port |= mask;					// Write 1
	*port &= ~mask;					// Write 0

	if (bit != 0)
	{
		_delay_us(8);				// the bus master must release the bus within 15us
	}
	else
	{
		_delay_us(80);				// the bus master must continue to hold the bus low for the duration of the time slot(at least 60us)
	}
	
	*port |= mask;

	if (bit != 0)
	{
		_delay_us(80);
	}
	else
	{
		_delay_us(2);
	}

	return bit != 0;
}

void write_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t data)
{
	uint8_t i = 0;

	for(i = 1; i != 0; i <<= 1)
	{
		write_bit_onewire(port, direction, port_in, mask, data & i);
	}
}

uint8_t read_bit_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask)
{
	uint8_t bit = 0;

	*direction |= mask;
	*port |= mask;					// Write 1
	*port &= ~mask;					// Write 0

	_delay_us(2);
	*direction &= ~mask;			// Set port as input
	_delay_us(5);
	bit = ((*port_in & mask) != 0);	// Read input
	_delay_us(60);

	return bit;
}

uint8_t read_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask)
{
	uint8_t data = 0;
	uint8_t i = 0;

	for(i = 1; i != 0; i <<= 1)
	{
		data |= read_bit_onewire(port, direction, port_in, mask) * i;
	}

	return data;
}