/*
 * UserMicros.h
 *
 * Created: 20.8.2021 23:48:06
 *  Author: batuh
 */ 


#ifndef USERMICROS_H_
#define USERMICROS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>

#define TIM0_PRESCALE 64
#define MICROSEC_VAL (1/(F_CPU / TIM0_PRESCALE))

volatile uint32_t Tim0_OvfValue = 0;

void Micros_Init(void);
uint32_t Micros(void);

#endif /* USERMİCROS_H_ */