/*
 * bh1750.c
 *
 * Created: 2019-09-11 11:40:23 AM
 *  Author: ceehb
 */ 

#include "bh1750.h"
#include "twowire.h"

void init_bh1750(void)
{
	start_wait_twowire(BH1750_ADDR | TWI_SLA_W);
	write_twowire(BH1750_H_RES_MODE);
	stop_twowire();
}

void read_bh1750_data(uint16_t* lux)
{
	uint16_t data = 0;

	start_wait_twowire(BH1750_ADDR | TWI_SLA_R);
	data = read_ack_twowire();
	data <<= 8;
	data |= read_nack_twowire();
	stop_twowire();

	*lux = (uint16_t)((double)data/1.2);
}