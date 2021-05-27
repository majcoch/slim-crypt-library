/*
 * uart.h
 *
 * Created: 27.04.2021 20:01:39
 *  Author: Micha³ Granda
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

#define UART_BAUD 19200

void uart_init(void);
uint8_t uart_read_byte(void);
void uart_write_byte(uint8_t byte);

#endif /* UART_H_ */