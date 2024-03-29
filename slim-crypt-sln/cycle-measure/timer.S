/*
 * timer_int.s
 *
 * Created: 03.03.2021 09:47:26
 *  Author: Micha� Granda
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

.extern overflows
.extern reminder

.global TIMER1_OVF_vect
.global cycle_count_start
.global cycle_count_stop

/* Timer 1 overflow interupt service routine */
TIMER1_OVF_vect:
	PUSH R16				// 2 cycles
	PUSH R17				// 2 cycles
	PUSH R18				// 2 cycles
	PUSH R19				// 2 cycles
	LDS R19, SREG			// 2 cycles

	LDI R16, 1				// 1 cycle
	LDS R17, overflows + 0	// 2 cycles
	LDS R18, overflows + 1	// 2 cycles

	ADD R17, R16			// 1 cycle
	CLR R16					// 1 cycle
	ADC R18, R16			// 1 cycle

	STS overflows + 0, R17	// 2 cycles
	STS overflows + 1, R18	// 2 cycles

	STS SREG, R19			// 2 cycles
	POP R19					// 2 cycles
	POP R18					// 2 cycles
	POP R17					// 2 cycles
	POP R16					// 2 cycles

	RETI					// 4 cycles

/* Start timer 1 */
cycle_count_start:
	CLR R18
	SBR R18, (1<<TOIE1)		// Enable interupt on overflow
	STS TIMSK1, R18
	CLR R18
	SBR R18, (1<<CS10)		// Enable counter
	STS TCCR1B, R18
	RET						// 4 clock cycles

/* Stop timer 1 */
cycle_count_stop:
	STS TCCR1B, R1			// Turn off timer - 2 cycles
	STS TIMSK1, R1			// Disable interupt
	LDS R18, TCNT1L			// Store current counter value
	LDS R19, TCNT1H
	STS reminder + 0, R18
	STS reminder + 1, R19 
	RET
