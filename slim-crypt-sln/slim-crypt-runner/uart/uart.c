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
	//UCSR0C |= (1<<UPM01);
}

void uart_read_byte(uint8_t* byte) {
	while (!(UCSR0A & (1<<RXC0)));
	*byte = UDR0;
}

void uart_write_byte(const uint8_t byte) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}

void uart_read(uint8_t* buff, const size_t len) {
	for (size_t i = 0; i < len; i++) {
		uart_read_byte(&buff[i]);
	}
}

void uart_write(const uint8_t* buff, const size_t len) {
	for (size_t i = 0; i < len; i++) {
		uart_write_byte(buff[i]);
	}
}
