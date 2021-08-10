/*
 * UserUart.c
 *
 * Created: 4.8.2021 18:25:24
 *  Author: batuh
 */ 

#include "UserUart.h"


ISR(USART_UDRE_vect) {
	if(UART_TX_Buffer.headPointer != UART_TX_Buffer.tailPointer) {
		UDR0 = UART_TX_Buffer.BUFFER[UART_TX_Buffer.tailPointer++];
		if(UART_TX_Buffer.tailPointer == BUFF_SIZE) {
			UART_TX_Buffer.tailPointer = 0;
		}
	}
	else {
		UCSR0B &= ~(1 << UDRIE0);
	}
}

ISR(USART_RX_vect) {
	UART_RX_Buffer.BUFFER[UART_RX_Buffer.headPointer] = UDR0;
	UART_RX_Buffer.headPointer = UART_RX_Buffer.headPointer + 1;
	if(UART_RX_Buffer.headPointer == BUFF_SIZE) {
		UART_RX_Buffer.headPointer = 0;
	}
}


void Init_Uart(uint32_t baudrate) {
	UCSR0B |= ((1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0));		// TX VE RX ETKÝNLEÞTÝRÝLDÝ
	UCSR0C &= ~((1 << UMSEL01) | (UMSEL00));	//ASENKRON MOD SEÇÝLDÝ
	UCSR0C &= ~((1 << UPM01) | (1 << UPM00));	//PARITY DISABLED
	UCSR0C &= ~(1 << USBS0);					// STOP BIT = 1BIT
	UCSR0C &= ~(1 << UCSZ02);
	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00)); 
	
	baudrate = F_CPU / (16*baudrate) - 1;
	UBRR0H = (baudrate & 0x0F00) >> 8;
	UBRR0L = (baudrate & 0x00FF);
	
	//Init_Buffer(&TX_Buffer);
}

void Uart_Transmit(uint8_t data) {
	UART_TX_Buffer.BUFFER[UART_TX_Buffer.headPointer++] = data;
	if(UART_TX_Buffer.headPointer == BUFF_SIZE) {
		UART_TX_Buffer.headPointer = 0;
	}
	UCSR0B |= (1 << UDRIE0);
}

void UartTransmit_Str(uint8_t *s) {
	while (*s>0)
	{
		Uart_Transmit(*s++);
	}
}

uint8_t Uart_Receive(void) {
	uint8_t UART_Tmp = 0;
	if(UART_RX_Buffer.tailPointer == UART_RX_Buffer.headPointer) {
		return -1;
	} else {
		UART_Tmp = UART_RX_Buffer.BUFFER[UART_RX_Buffer.tailPointer++];
		if(UART_RX_Buffer.tailPointer == BUFF_SIZE) {
			UART_RX_Buffer.tailPointer = 0;
		}
	}
	return UART_Tmp;
}

void Uart_Flush(void) {
	UartBuffer_t *rxBuff = &UART_RX_Buffer;
	memset(rxBuff->BUFFER, '\0', BUFF_SIZE);
	rxBuff->headPointer = 0;
	rxBuff->tailPointer = 0;
}

bool Uart_Available(void) {
	return (UART_RX_Buffer.headPointer != UART_RX_Buffer.tailPointer?1:0);
}
