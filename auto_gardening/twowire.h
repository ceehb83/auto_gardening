/*
 * twowire.h
 *
 * Created: 2019-09-10 10:23:55 PM
 *  Author: ceehb
 */ 


#ifndef TWOWIRE_H_
#define TWOWIRE_H_

#define SCL_CLOCK			160000UL

#define TWI_SLA_W			0x0			// low level at SDA
#define TWI_SLA_R			0x1			// high level at SDA

#define TWI_START			0x08
#define TWI_REP_START		0x10
#define TWI_MTX_SLA_ACK		0x18
#define TWI_MTX_SLA_NACK	0x20
#define TWI_MTX_DAT_ACK		0x28
#define TWI_MTX_DAT_NACK	0x30
#define TWI_MTX_ARB_LOST	0x38

#include <inttypes.h>

void init_twowire(void);
uint8_t start_twowire(uint8_t address);
void start_wait_twowire(uint8_t address);
void stop_twowire(void);
uint8_t write_twowire(uint8_t data);
uint8_t read_ack_twowire(void);
uint8_t read_nack_twowire(void);

#endif /* TWOWIRE_H_ */