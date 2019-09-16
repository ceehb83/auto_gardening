/*
 * bh1750.h
 *
 * Created: 2019-09-11 11:41:29 AM
 *  Author: ceehb
 */ 


#ifndef BH1750_H_
#define BH1750_H_

#include <inttypes.h>

#define BH1750_ADDR			(0x23 << 1)			// device address

// resolution modes
#define BH1750_H_RES_MODE	0x10		// continuously h-resolution mode, 1 lux resolution, 120ms
#define BH1750_H_RES_MODE2	0x11		// continuously h-resolution mode, 0.5 lux resolution, 120ms
#define BH1750_L_RES_MODE	0x13		// continuously l_resolution mode, 4 lux resolution, 16ms

void init_bh1750(void);
void read_bh1750_data(uint16_t* lux);

#endif /* BH1750_H_ */