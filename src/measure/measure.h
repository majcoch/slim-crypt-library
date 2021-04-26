/*
 * measure.h
 *
 * Created: 03.03.2021 10:18:29
 *  Author: Micha³ Granda
 */ 


#ifndef MEASURE_H_
#define MEASURE_H_

#include <stdint.h>
#include <avr/io.h>

#define TIMER_CNT_MAX		65536		// Number of cycles timer can count

#define TIMER_ISR_RESPONSE	6			// Number of cycles it takes CPU to start
										// executing ISR code
										
#define TIMER_ISR_EXEC		13			// Number of cycles ISR takes to execute

#define TIMER_START_LAT		4			// Number of cycles it takes to return from
										// cycle_count_start routine
										
#define TIMER_STOP_LAT		6			// Number of cycles it takes to shut down counter
										// starting from calling cycle_count_stop routine

void cycle_count_init(void);
extern void cycle_count_start(void);
extern void cycle_count_stop(void);
uint32_t cycle_count_get();

#endif /* MEASURE_H_ */