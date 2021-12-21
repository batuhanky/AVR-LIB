/*
 * API_MCP4725.c
 *
 *  Created on: Dec 22, 2021
 *      Author: batuhan
 */

#include "API_MCP4725.h"

void API_MCP4725_SetVoltage(uint16_t voltage) {
	uint8_t lsb, msb;
	msb = (uint8_t)(voltage / 16);
	lsb = (uint8_t)((voltage % 16) << 4);

	I2C_Start();
	I2C_Write(MCP4725_WRITE_CMD(MCP4725_ADDR));
	I2C_Write(MCP4725_WRITE_DAC_REGISTER);
	I2C_Write(msb);
	I2C_Write(lsb);
	I2C_Stop();
}
