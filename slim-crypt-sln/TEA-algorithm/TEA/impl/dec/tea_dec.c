/*
 * tea_dec.c
 *
 * Created: 26.05.2021 15:38:11
 *  Author: Micha³ Granda
 */ 
#include "tea_dec.h"

#include "../comm/tea_common.h"

uint64_t tea_decrypt_block(const tea_context_t* context, uint64_t block) {
	uint32_t v[] = { (block >> 32), ((uint32_t)block) };
	const uint32_t* k = context->user_key;
	
	uint32_t sum = DECRYPT_SUM;

	for (uint8_t i = 0; i < 32; i++) {
		v[1] -= ((v[0] << 4) + k[2]) ^ (v[0] + sum) ^ ((v[0] >> 5) + k[3]);
		v[0] -= ((v[1] << 4) + k[0]) ^ (v[1] + sum) ^ ((v[1] >> 5) + k[1]);
		sum -= MAGIC_CONSTANT;
	}
	
	return ((uint64_t)v[0] << 32) | v[1];
}

void tea_decrypt(const tea_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		create_block(&data[i], &block);
		block = tea_decrypt_block(context, block);
		destroy_block(&data[i], &block);
	}
}
