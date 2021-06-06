/*
 * uart.h
 *
 * Created: 27.04.2021 20:01:39
 *  Author: Micha� Granda
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>

#define UART_BAUD 9600

void uart_init(void);

void uart_read_byte(uint8_t* byte);
void uart_write_byte(const uint8_t byte);

void uart_read(uint8_t* buff, const size_t len);
void uart_write(uint8_t* buff, const size_t len);

#endif /* UART_H_ */