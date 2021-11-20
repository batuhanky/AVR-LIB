/*
 * UserADC.h
 *
 *  Created on: Nov 20, 2021
 *      Author: batuhan
 */

#ifndef USERADC_H_
#define USERADC_H_

#include <avr/io.h>
#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t ADC_Channel);

#endif /* USERADC_H_ */
