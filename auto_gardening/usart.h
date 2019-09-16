/*
 * usart.h
 *
 * Created: 2019-09-03 1:38:13 PM
 *  Author: ceehb
 */ 


#ifndef USART_H_
#define USART_H_

#include "config.h"
#include <inttypes.h>

#define FOSC			F_CPU
#define BAUD			9600
#define UBRR_VALUE		((FOSC/16/BAUD) - 1)

void init_usart(void);
void send_data_usart(uint8_t data);
void put_string_usart(char* stringPtr);

#endif /* USART_H_ */