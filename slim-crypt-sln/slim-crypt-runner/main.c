/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Micha³ Granda
 */ 

#include <avr/io.h>
#include "AES/aes.h"

int main(void) {
    /* Replace with your application code */
	uint8_t message[] = "This is a message we will encrypt with AES!";
	aes_128_context_t aes = { { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, { 0 } };

	aes_init(&aes);
	aes_128_encrypt(&aes, message, 32);
	aes_128_decrypt(&aes, message, 32);
	
    while (1) {}
}

