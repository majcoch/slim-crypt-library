/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Micha³ Granda
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "uart/uart.h"

static FILE uart_str  = FDEV_SETUP_STREAM(uart_write_byte, uart_read_byte, _FDEV_SETUP_RW);

int main(void) {
    /* Replace with your application code */
	uart_init();
	stdout = stdin = &uart_str;
	
	//printf("Hello, World!");
    while (1) {
		uint8_t byte = uart_read_byte();
		uart_write_byte(byte);	
	}
}

