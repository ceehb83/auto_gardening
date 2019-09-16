/*
 * ds18b20.h
 *
 * Created: 2019-09-03 4:41:05 PM
 *  Author: ceehb
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include <inttypes.h>

#define DS18B20_ERROR_OK			0
#define DS18B20_ERROR_COMM			1
#define DS18B20_ERROR_CRC			2
#define DS18B20_ERROR_PULL			3
#define DS18B20_ERROR_OTHER			4
#define DS18B20_OK					DS18B20_ERROR_OK

#define DS18B20_COMMAND_READ_ROM	0x33
#define DS18B20_COMMAND_MATCH_ROM	0x55
#define DS18B20_COMMAND_SKIP_ROM	0xCC
#define DS18B20_COMMAND_CONVERT		0x44
#define DS18B20_COMMAND_WRITE_SP	0x4E
//#define DS18B20_COMMAND_READ_SP		0x8E
#define DS18B20_COMMAND_READ_SP		0xBE
#define DS18B20_COMMAND_COPY_SP		0x48
#define DS18B20_COMMAND_SEARCH_ROM	0xF0

#define DS18B20_RES09				(0 << 5)
#define DS18B20_RES10				(1 << 5)
#define DS18B20_RES11				(2 << 5)
#define DS18B20_RES12				(3 << 5)

#define DS18B20_MULTIPLIER			16

uint8_t convert_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom);
void match_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom);
uint8_t read_ds18b20_scratchpad(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom, uint8_t* sp);
uint8_t read_ds18b20(volatile uint8_t* port, volatile uint8_t* direction, volatile uint8_t* port_in, uint8_t mask, uint8_t* rom, int16_t* temperature);

#endif /* DS18B20_H_ */

