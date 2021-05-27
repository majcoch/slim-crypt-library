/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Micha³ Granda
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "uart/uart.h"

int main(void) {
    /* Replace with your application code */
	uart_init();
	
    while (1) {
		uint8_t byte = uart_read_byte();
		uart_write_byte(byte);	
	}
}

