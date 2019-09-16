/*
 * timer.c
 *
 * Created: 2019-09-11 2:41:09 PM
 *  Author: ceehb
 */ 

#include "timer.h"
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t counter = 0;
volatile uint8_t flag = 0;
volatile uint8_t T1ovs1 = 0, T1ovs2 = 0;
volatile uint8_t capt1 = 0, capt2 = 0, capt3 = 0;
volatile uint8_t dutyCycle = 0;

ISR(TIMER1_CAPT_vect)
{
	if(flag == 0)
	{
		capt1 = ICR1;
		TCCR1B &= ~(1 << ICES1); //falling edge
		T1ovs2 = 0;
	}
	else if(flag == 1)
	{
		capt2 = ICR1;
		TCCR1B |= (1 << ICES1);	//rising edge
		T1ovs1 = T1ovs2;
	}
	else if(flag == 2)
	{
		capt3 = ICR1;
		TIMSK1 &= ~( (1 << ICIE1) | (1 << TOIE1) );
	}
	flag++;
}


ISR(TIMER1_OVF_vect)
{
	// LED check
	// PORTB ^= ((1 << PORTB1) | (1 << PORTB2));
	
	T1ovs2++;

	TCNT1 = 63536;
}

void init_timer1(void)
{
	//TCNT1 = 61535;
	TCNT1 = 63536;
	/* |	COM1A1	|	COM1A0	|	flCOM1B1	|	COM1B0	|	-	|	-	|	WGM11	|	WGM10	| */
	/* TCCR1A = 0x00; -> disable all waveform functions */
	/* p134 - Normal port operation, OC1A/OC1B disconnected */
	TCCR1A = 0x00;	

	/* |	ICNC1	|	ICES1	|	-	|	WGM13	|	WGM12	|	CS12	|	CS11	|	CS10	| */
	/*  p136
		0x24 - ICES1: 1, CS12: 1 
		ICES1: 1				- rising edge triggered
		CS12 CS11 CS10: 010		- clk/8(From prescaler)
		CS12 CS11 CS10: 101		- clk/1024(From prescaler)
	*/
	//TCCR1B = ( (1 << ICES1) | (1 << CS12) | (1 << CS10) );
	TCCR1B = ( (1 << ICES1) | (1 << CS11) );
	
	/* |	-	|	-	|	ICIE1	|	-	|	-	|	OCIE1B	|	OCIE1A	|	TOIE1	| */
	/*
		p139
		ICIE1: TImer/Counter1, Input Capture Interrupt Enable
		TOIE1: Timer/Counter1, Overflow Interrupt Enable
	*/
	TIMSK1 = ( (1 << ICIE1) | (1 << TOIE1) );

	sei();
}