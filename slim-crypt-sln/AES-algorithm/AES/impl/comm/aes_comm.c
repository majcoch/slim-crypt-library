/*
 * aes_comm.c
 *
 * Created: 26.05.2021 11:17:23
 *  Author: Micha³ Granda
 */ 
#include "aes_comm.h"

#define GAL_MUL_2(x)  ((((x) << 1) ^ (0x1B & (((x) >> 7) * 0xFF))) & 0xFF)

void aes_add_round_key(uint8_t* state, const uint8_t* key) {
	for (uint8_t i = 0; i < 16; i++) {
		state[i] ^= key[i];
	}
}

uint8_t aes_galois_multiply(uint8_t a, uint8_t b) {
	uint8_t result = 0;

	while (a) {
		result ^= b & ((a & 0x01) * 0xFF);
		b = GAL_MUL_2(b);
		a >>= 1;
	}

	return result;
}
