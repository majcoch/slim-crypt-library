/*
 * measure.c
 *
 * Created: 04.03.2021 11:24:52
 *  Author: Micha³ Granda
 */ 


#include "measure.h"

volatile uint8_t overflows;
volatile uint16_t reminder;

void cycle_count_init(void) {
	overflows = 0x00;
	reminder = 0x0000;
	TCNT1L = 0;
	TCNT1H = 0;
}

uint32_t cycle_count_get() {
	uint32_t result = (uint32_t)(TIMER_CNT_MAX - (TIMER_ISR_RESPONSE+TIMER_ISR_EXEC)) * (uint32_t)overflows;
	result += (reminder - TIMER_START_LAT - TIMER_STOP_LAT);
	return result;
}