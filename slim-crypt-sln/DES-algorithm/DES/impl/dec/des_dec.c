/*
 * des_dec.c
 *
 * Created: 26.05.2021 15:03:54
 *  Author: Micha³ Granda
 */ 
#include "des_dec.h"

#include "../../data/des_data.h"
#include "../comm/des_common.h"

uint64_t des_decrypt_block(const des_context_t* context, const uint64_t block) {
	uint64_t permutated_data = perform_permutation(block, ip, 64, 64);

	uint32_t l_block = DATA_UPPER_HALF(permutated_data);
	uint32_t r_block = DATA_LOWER_HALF(permutated_data);

	for (uint8_t i = 0; i < 16; i++) {
		uint32_t tmp = l_block;
		l_block = r_block;
		r_block = tmp ^ f(r_block, context->expanded_key[15 - i]);
	}

	// combine R + L
	uint64_t result = ((uint64_t)(r_block) << 32) | l_block;
	result = perform_permutation(result, inv_ip, 64, 64);

	return result;
}

void des_decrypt(const des_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		create_block(&data[i], &block);
		block = des_decrypt_block(context, block);
		destroy_block(&data[i], &block);
	}
}
