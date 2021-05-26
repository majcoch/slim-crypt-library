/*
 * blowfish_dec.c
 *
 * Created: 26.05.2021 16:16:59
 *  Author: Micha³ Granda
 */ 
#include "blowfish_dec.h"

#include "../../data/blowfish_data.h"
#include "../comm/blowfish_common.h"

uint64_t blowfish_decrypt_block(uint64_t block) {
	uint32_t L = (block >> 32);
	uint32_t R = (uint32_t)(block);
	
	for (int8_t i = 16; i > 0; i -= 2) {
		L ^= blowfish_p_box[i + 1];
		R ^= f(L);
		R ^= blowfish_p_box[i];
		L ^= f(R);
	}
	L ^= blowfish_p_box[1];
	R ^= blowfish_p_box[0];

	uint32_t tmp = L;
	L = R;
	R = tmp;
	
	return ((uint64_t)L << 32) | R;	
}

void blowfish_decrypt(uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		create_block(&data[i], &block);
		block = blowfish_decrypt_block(block);
		destroy_block(&data[i], &block);
	}
}
