/*
 * twowire.c
 *
 * Created: 2019-09-10 10:23:44 PM
 *  Author: ceehb
 */ 
#include "config.h"
#include "twowire.h"
#include <avr/io.h>

void init_twowire(void)
{
	/* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
		  
	/* |	TWS7	|	TWS6	|	TWS5	|	TWS4	|	TWS3	|	-	|	TWPS1	|	TWPS0	| */
	/* TWPS[1..0] - (00): 1 / (01): 4 / (10): 16 / (11): 64 */
	TWSR = 0;                         /* no prescaler */

	/* |	TWBR7	|	TWBR6	|	TWBR5	|	TWBR4	|	TWBR3	|	TWBR2	|	TWBR1	|	TWBR0	| */
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */
	//TWBR = 42;  /* must be > 10 for stable operation */
}

uint8_t start_twowire(uint8_t address)
{
	uint8_t twi_status = 0;

	// send START condition
	TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));

	// wait until transmission completed
	while(!(TWCR & (1 << TWINT)));

	// check TWI status register. Mask prescaler bits.
	twi_status = TWSR & 0xF8;
	if((twi_status != TWI_START) && (twi_status != TWI_REP_START))
	{
		return 1;	// error
	}

	// send device address
	TWDR = address;
	TWCR = ((1 << TWINT) | (1 << TWEN));

	// wait until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1 << TWINT)));

	// check TWI status register. Mask prescaler bits.
	twi_status = TWSR & 0xF8;
	if((twi_status != TWI_MTX_SLA_ACK) && (twi_status != TWI_MTX_SLA_NACK))
	{
		return 1;	// error
	}

	return 0;
}

void start_wait_twowire(uint8_t address)
{
	uint8_t twi_status;

	while(1)
	{
		// Send START condition
		TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));

		// Wait until transmission completed
		while(!(TWCR & (1 << TWINT)));

		// check value of TWI status register. Mask prescaler bits.
		twi_status = TWSR & 0xF8;
		if((twi_status != TWI_START) && (twi_status != TWI_REP_START)) continue;

		// send device address
		TWDR = address;
		TWCR = ((1 << TWINT) | (1 << TWEN));

		// Wait until transmission completed
		while(!(TWCR & (1 << TWINT)));

		// Check value of TWI status register. Mask prescaler bits.
		twi_status = TWSR & 0xF8;
		if((twi_status == TWI_MTX_SLA_NACK) || (twi_status == TWI_MTX_DAT_NACK))
		{
			// device busy, send stop condition to terminate write operation
			TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO));

			// Wait until stop condition is executed and bus released
			while(TWCR & (1 << TWSTO));

			continue;
		}
		break;
	}
}

void stop_twowire(void)
{
	// Send STOP condition
	TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));

	// When the STOP condition is executed on the bus, the TWSTO bit is cleared automatically
	while(TWCR & (1 << TWSTO));
}

uint8_t write_twowire(uint8_t data)
{
	uint8_t twi_status = 0;

	// Send data
	TWDR = data;
	TWCR = ((1 << TWINT) | (1 << TWEN));

	// Wait until transmission completed
	while(!(TWCR & (1 << TWINT)));

	twi_status = TWSR & 0xF8;
	if(twi_status != TWI_MTX_DAT_ACK)
	{
		return 1;	// error
	}
	return 0;
}

uint8_t read_ack_twowire(void)
{
	TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA));

	while(!(TWCR & (1 << TWINT)));

	return TWDR;
}

uint8_t read_nack_twowire(void)
{
	TWCR = ((1 << TWINT) | (1 << TWEN));

	while(!(TWCR & (1 << TWINT)));

	return TWDR;
}