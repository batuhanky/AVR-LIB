/*
 * UserADC.c
 *
 *  Created on: Nov 20, 2021
 *      Author: batuhan
 */


#include "UserADC.h"

void ADC_Init(void) {
	ADMUX |= (1 << REFS0);	//ADC Voltage Reference Selected
	ADCSRA |= ( (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADIF));
}

uint16_t ADC_Read(uint8_t ADC_Channel) {
	ADMUX &= 0xF0;
	ADMUX |= (ADC_Channel & 0x0F);
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADIF));
	return ADCW;
}
