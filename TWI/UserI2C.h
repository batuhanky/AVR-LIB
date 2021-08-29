/*
 * UserI2C.h
 *
 * Created: 29.8.2021 22:43:22
 *  Author: batuh
 */ 


#ifndef USERI2C_H_
#define USERI2C_H_

#include <avr/io.h>
#include <util/delay.h>

#define SCL_100kHZ	100000
#define SCL_PRESCALER	1
#define SCL_TWBR	((F_CPU / SCL_100kHZ) - 16) / (2 * SCL_PRESCALER))

void I2C_Init(void);
void I2C_Start(void);
void I2C_RStart(void);
void I2C_Stop(void);
void I2C_Send(uint8_t);
uint8_t I2C_Read(uint8_t);


#endif /* USERI2C_H_ */