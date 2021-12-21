/*
 * API_MCP4725.h
 *
 *  Created on: Dec 22, 2021
 *      Author: batuhan
 */

#ifndef API_MCP4725_H_
#define API_MCP4725_H_

#include "UserI2C.h"

#define MCP4725_ADDR	0x60

#define MCP4725_WRITE_DAC_REGISTER 0x40		//POWER DOWN SELECT BITS ARE 00
#define MCP4725_WRITE_CMD(ADDR)	((ADDR << 1) | TW_WRITE)
#define MCP4725_READ_CMD(ADDR)	((ADDR << 1) | TW_READ)

void API_MCP4725_SetVoltage(uint16_t voltage);



#endif /* API_MCP4725_H_ */
