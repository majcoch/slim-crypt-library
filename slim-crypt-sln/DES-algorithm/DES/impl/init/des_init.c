/*
 * des_init.c
 *
 * Created: 26.05.2021 14:43:51
 *  Author: Micha³ Granda
 */ 
#include "des_init.h"

#include "../../data/des_data.h"
#include "../comm/des_common.h"

#define KEY_LOWER_HALF(x) (x >> 28)
#define KEY_UPPER_HALF(x) (x & 0x0fffffff)

uint32_t left_rotate_subkey(const uint32_t key, const uint8_t rotate) {
	uint32_t result = 0;
	uint32_t tmp_key = key;

	for (uint8_t i = 0; i < rotate; i++) {
		uint8_t tmp_bit = ((tmp_key & ((uint32_t)1 << 27)) >> 27);
		result = (((tmp_key << 1)) | tmp_bit) & 0x0FFFFFFF;
		tmp_key = result;
	}

	return result;
}

void generate_keys(const uint64_t key, uint64_t keys[]) {
	uint64_t compressed_key = perform_permutation(key, pc_1, 64, 56);
	uint32_t c_key = KEY_LOWER_HALF(compressed_key);
	uint32_t d_key = KEY_UPPER_HALF(compressed_key);

	for (uint8_t i = 0; i < 16; i++) {
		c_key = left_rotate_subkey(c_key, key_shift[i]);
		d_key = left_rotate_subkey(d_key, key_shift[i]);
		uint64_t new_key = ((uint64_t)(c_key) << 28) | d_key;

		keys[i] = perform_permutation(new_key, pc_2, 56, 48);
	}
}

void des_init(des_context_t* context) {
	generate_keys(context->user_key, context->expanded_key);
}
