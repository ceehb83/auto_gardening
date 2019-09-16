/*
 * usart.c
 *
 * Created: 2019-09-03 2:33:20 PM
 *  Author: ceehb
 */ 

 #include "usart.h"
 #include <avr/io.h>

 void init_usart(void)
 {
	 /* Set Baud Rate */
	 UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	 UBRR0L = (uint8_t)(UBRR_VALUE);
	 
	 /* |	RXCIEn	|	TXCIEn	|	UDRIEn	|	RXENn	|	TXENn	|	UCSZn2	|	RXB8n	|	TXB8n	| */
	 UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	 /* |	UMSELn1	|	UMSELn0	|	UPMn1	|	UPMn9	|	USBSn	|	UCSZn1	|	UCSZn0	|	UCPOLn	| */
	 // Set frame: Asynchronous, No Parity, 8 data bits, 1 stop bit
	 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	
 }

 void send_data_usart(unsigned char data)
 {
	 while(!(UCSR0A & (1<<UDRE0)));
	 UDR0 = data;
 }

 void put_string_usart(char* stringPtr)
 {
	 while(*stringPtr != 0x00)
	 {
		 send_data_usart(*stringPtr);
		 stringPtr++;
	 }
 }
