/*
 * onewire.h
 *
 * Created: 2019-09-03 3:07:01 PM
 *  Author: ceehb
 */ 


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <inttypes.h>

#define ONEWIRE_COMM_OK		0	// Communication success
#define ONEWIRE_COMM_ERR	1	// Communication failure

uint8_t init_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask);
uint8_t write_bit_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t bit);
void write_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t data);
uint8_t read_bit_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask);
uint8_t read_onewire(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask);

#endif /* ONEWIRE_H_ */