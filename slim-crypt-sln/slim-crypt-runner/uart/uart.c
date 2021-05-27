/*
 * uart.c
 *
 * Created: 27.04.2021 20:05:40
 *  Author: Micha³ Granda
 */ 


#include "uart.h"

#define MYUBRR ((F_CPU+UART_BAUD*8UL)/(16UL *UART_BAUD)-1)

void uart_init(void) {
	UBRR0L = (uint8_t)(MYUBRR);
	UBRR0H = (uint8_t)(MYUBRR>>8);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UPM01);
}

uint8_t uart_read_byte(void) {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void uart_write_byte(uint8_t byte) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}
