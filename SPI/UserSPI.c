/*
 * UserSPI.c
 *
 *  Created on: Nov 26, 2021
 *      Author: batuhan
 */

#include "UserSPI.h"

ISR(SPI_STC_vect) {
	if(SPSR & 0x40) {
		SPI_Receive_Data = 0;
		SPI_Transmit_Done = 1;
	}	else {
		SPI_Receive_Data = SPDR;
		SPI_Transmit_Done = 1;
	}
}

void SPI_Init(SPI_MODE_t spi_mode) {

	SPCR = 0x00;		//SPI CONTROL REGISTER RESET
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);		//MOSI SCK SS PINS ARE OUTPUT
	DDRB &= ~(1 << MISO);
	PORTB |= (1<<SS);		//SS PIN IS HIGH (DEFAULT)

	switch (spi_mode) {
		case SPI_MODE0:		//CPOL = 0, CHPA = 0
			SPCR |= ( (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0) );
			break;
		case SPI_MODE1:		//CPOL = 0, CPHA = 1
			SPCR |= ( (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << CPHA) );
			break;
		case SPI_MODE2:		//CPOL = 1, CPHA = 0
			SPCR |= ( (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << CPOL) );
			break;
		case SPI_MODE3:		//CPOL = 1, CPHA = 1
			SPCR |= ( (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << CPHA) | (1 << CPOL) );
			break;
		default:			//DEFAULT SPI SETTINGS (CPOL = 0, CPHA = 0)
			SPCR |= ( (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0) );
			break;
	}
}

static void SPI_Transmit(uint8_t *tx_data, uint8_t *rx_data) {
	SPI_Transmit_Done = 0;
	SPDR = *tx_data;
	while(SPI_Transmit_Done == 0);
	*rx_data = SPDR;
}

void SPI_TransmitReceive(uint8_t *tx_data, uint8_t *rx_data, uint8_t len) {
	PORTB &= ~(1 << SS);
	_delay_us(10);
	for(uint8_t i=0; i < len; i++) {
		SPI_Transmit(tx_data++, rx_data++);
	}
	PORTB |= (1 << SS);
	_delay_us(100);

}



