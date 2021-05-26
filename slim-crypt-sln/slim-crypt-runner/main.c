/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Micha� Granda
 */ 

#include <avr/io.h>
//#include "AES/aes.h"
//#include "DES/des.h"
#include "TEA/tea.h"

int main(void) {
   
	uint8_t message[] = "This is a message we will encrypt with AES!";
	
	/* AES encrypting and decrypting example */
	//aes_128_context_t aes = { { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, { 0 } };
	//aes_init(&aes);
	//aes_128_encrypt(&aes, message, 32);
	//aes_128_decrypt(&aes, message, 32);
	
	/* DES encrypting and decrypting example */
	//des_context_t des = {0xAABB09182736CCDD, {0}};
	//des_init(&des);
	//des_encrypt(&des, message, 8);
	//des_decrypt(&des, message, 8);
	
	/* TEA encrypting and decrypting example */
	tea_context_t tea = { {0x12, 0x65, 0x22, 0x55} };
	tea_encrypt(&tea, message, 8);
	tea_decrypt(&tea, message, 8);
	
    while (1) {}
}

