/*
 * blowfish_enc.c
 *
 * Created: 26.05.2021 15:51:39
 *  Author: Micha³ Granda
 */ 
#include "blowfish_enc.h"

#include "../../data/blowfish_data.h"
#include "../comm/blowfish_common.h"

uint64_t blowfish_encrypt_block(uint64_t block) {
	uint32_t L = (block >> 32);
	uint32_t R = (uint32_t)(block);
	
    for (uint8_t i = 0; i < 16; i += 2) {
	    L ^= p_box[i];
	    R ^= f(L);
	    R ^= p_box[i + 1];
	    L ^= f(R);
    }
    L ^= p_box[16];
    R ^= p_box[17];

    uint32_t tmp = L;
    L = R;
    R = tmp;
	
	return ((uint64_t)L << 32) | R;
}

void blowfish_encrypt(uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		create_block(&data[i], &block);
		block = blowfish_encrypt_block(block);
		destroy_block(&data[i], &block);
	}
}
