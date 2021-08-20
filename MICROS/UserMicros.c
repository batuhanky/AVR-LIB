/*
 * UserMicros.c
 *
 * Created: 20.8.2021 23:50:16
 *  Author: batuh
 */ 

#include "UserMicros.h"

void Micros_Init(void) {
	TCCR0B |= ((1 << CS01) | (1 << CS00));		//Set Timer0 prescaler CPU_CLOCK/64
	
	TIMSK0 |= (1 << TOIE0);						//Enable Timer0 overflow interrupt
	TCNT0 = 0;									//Set Timer0 Counter value zero
	
	sei();										//Enable global interrupts 
}

uint32_t Micros(void) {
	uint32_t microsReturn = 0;
	uint8_t cntValue = 0;
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		microsReturn = Tim0_OvfValue;
		cntValue = TCNT0;
	}
	return (((microsReturn << 8) + cntValue) * MICROSEC_VAL);
}

ISR(TIMER0_OVF_vect) {
	Tim0_OvfValue++;
}