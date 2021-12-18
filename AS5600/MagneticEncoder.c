/*
 * MagneticEncoder.c
 *
 *  Created on: Dec 12, 2021
 *      Author: batuhan
 */

#include "MagneticEncoder.h"


void API_AS5600_Init(AS5600_t *as5600, uint8_t _chip_address) {
	as5600->chip_address = _chip_address;
	as5600->cpr = pow(2, as5600->resolution);

	I2C_Init();
}

uint16_t API_AS5600_GetRaw_Angle(AS5600_t *as5600) {
	return (API_AS5600_Read(as5600->angle_reg));
}

float API_AS5600_Get_Angle(AS5600_t *as5600) {
	return ( API_AS5600_GetRaw_Angle(as5600) / (float)as5600->cpr ) * _2PI;
}

uint16_t API_AS5600_Read(uint8_t msb_address) {
	uint16_t readArr[2] = {0};
	uint16_t readVal = 0;

	I2C_Start();

	I2C_Write(AS5600_WRITE);
	I2C_Write(msb_address);

	I2C_RStart();

	I2C_Write(AS5600_READ);
	readArr[0] = I2C_Read(1);
	readArr[1] = I2C_Read(0);

	I2C_Stop();

	readArr[0] = ((readArr[0] & 0x0F) << 8);
	readArr[1] = (readArr[1] & 0xFF);

	readVal = readArr[0] | readArr[1];

	return readVal;

}
