/*
 * UserI2C.c
 *
 * Created: 29.8.2021 22:44:58
 *  Author: batuh
 */ 

#include "UserI2C.h"

void I2C_Init(void) {
	TWSR = 0x00;
	TWBR = SCL_TWBR;
	TWCR = (1 << TWEN);
}

void I2C_Start(void) {
	TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
	while(!(TWCR & (1 << TWINT)));
}

void I2C_RStart(void) {
	TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
	while(!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
	TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
	_delay_us(100);
} 

void I2C_Send(uint8_t data) {
	TWDR = data;
	TWCR = ((1 << TWINT) | (1 << TWEN));
	while(!(TWCR & (1 << TWINT)));
}

uint8_t I2C_Read(uint8_t ack) {
	TWCR = ((1 << TWINT) | (1 << TWEN) | (ack << TWEA));
	while(!(TWCR &  (1 << TWINT)));
	return TWDR;
}