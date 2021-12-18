/*
 * MagneticEncoder.h
 *
 *  Created on: Dec 12, 2021
 *      Author: batuhan
 */

#ifndef MAGNETICENCODER_H_
#define MAGNETICENCODER_H_

#include <stdint.h>
#include <math.h>
#include "UserI2C.h"

#define AS5600_ADDRESS	0x36
#define AS5600_READ	    ((AS5600_ADDRESS << 1) | 1)
#define AS5600_WRITE   	((AS5600_ADDRESS << 1) | 0)

#define AS5600_RAW_ANGLE	0x0C

#define _2PI 6.28318530718f

typedef struct AS5600 {

	uint8_t chip_address;
	uint16_t resolution;
	uint8_t angle_reg;
	uint16_t cpr;


}AS5600_t;

void API_AS5600_Init(AS5600_t * as5600, uint8_t _chip_address);
uint16_t API_AS5600_Read(uint8_t msb_address);
uint16_t API_AS5600_GetRaw_Angle(AS5600_t *as5600);
float API_AS5600_Get_Angle(AS5600_t *as5600);

#endif /* MAGNETICENCODER_H_ */
