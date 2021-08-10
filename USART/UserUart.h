/*
 * UserUart.h
 *
 * Created: 4.8.2021 18:25:06
 *  Author: batuh
 */ 


#ifndef USERUART_H_
#define USERUART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define UART_9600	9600
#define UART_115200	115200

#define BUFF_SIZE 20

typedef struct {
	volatile uint8_t headPointer;
	volatile uint8_t tailPointer;
	uint8_t BUFFER[BUFF_SIZE];
}UartBuffer_t;

UartBuffer_t UART_RX_Buffer;
UartBuffer_t UART_TX_Buffer;

void Init_Uart(uint32_t baudrate);
void Uart_Flush(void);
void Uart_Transmit(uint8_t data);
void UartTransmit_Str(uint8_t *s);
uint8_t Uart_Receive(void);
bool Uart_Available(void);


#endif /* USERUART_H_ */