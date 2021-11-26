/*
 * UserSPI.h
 *
 *  Created on: Nov 26, 2021
 *      Author: batuhan
 */


#ifndef USERSPI_H_
#define USERSPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#define SS		PORTB2
#define MOSI    PORTB3
#define MISO	PORTB4
#define SCK     PORTB5

typedef enum {
		SPI_MODE0 = 0,
		SPI_MODE1,
		SPI_MODE2,
		SPI_MODE3
}SPI_MODE_t;

SPI_MODE_t SPI_MODE;

volatile uint8_t SPI_Transmit_Done;
volatile uint8_t SPI_Receive_Data;

void SPI_Init(SPI_MODE_t spi_mode);
static void SPI_Transmit(uint8_t *tx_data, uint8_t *rx_data);
void SPI_TransmitReceive(uint8_t *tx_data, uint8_t *rx_data, uint8_t len);

#endif /* USERSPI_H_ */
