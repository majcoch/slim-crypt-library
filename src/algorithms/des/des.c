/*
 * des.c
 *
 * Created: 26.05.2021 19:30:58
 *  Author: Micha³ Granda
 */ 
#include "des.h"

#include "data/des_data.h"

#ifdef __AVR__
	#include <avr/pgmspace.h>
	#define FLASH_ACCESS(x) pgm_read_byte(&(x))
#else
	#define FLASH_ACCESS(x) (x)
#endif // __AVR__

#define KEY_LOWER_HALF(x) (x >> 28)
#define KEY_UPPER_HALF(x) (x & 0x0fffffff)

#define DATA_UPPER_HALF(x) (uint32_t)(x >> 32)
#define DATA_LOWER_HALF(x) (uint32_t)(x)

uint64_t des_perform_permutation(const uint64_t data, const uint8_t* tab, const uint8_t in_bits, const uint8_t out_bits) {
	uint64_t result = 0;

	for (uint8_t i = 0; i < out_bits; i++) {
		uint64_t mask = ((uint64_t)1 << (in_bits - FLASH_ACCESS(tab[i])));
		result |= (((data & mask) >> (in_bits - FLASH_ACCESS(tab[i]))) << (out_bits - i - 1));
	}

	return result;
}

uint64_t des_f(const uint32_t r_block, const uint64_t key) {
	// Expand and XOR with key
	uint64_t permutated_block = des_perform_permutation(r_block, des_expand_table, 32, 48);
	permutated_block ^= key;

	// Apply s-box
	uint64_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		uint8_t bit_box = (permutated_block >> ((7 - i) * 6)) & 0b111111;

		uint8_t row = ((bit_box >> 4) & 0b000010) | (bit_box & 0b000001);
		uint8_t column = (bit_box & 0b011110) >> 1;

		uint8_t substitution = FLASH_ACCESS(des_s_box[i][row][column]);

		result |= ((uint64_t)(substitution) << ((7 - i) * 4));
	}

	result = des_perform_permutation(result, des_p, 32, 32);
	return result;
}

void des_create_block(const uint8_t* data, uint64_t* block) {
	uint8_t shift = 56;
	*block = 0;
	for (uint8_t i = 0; i < 8; i++) {
		*block |= (uint64_t)(data[i]) << shift;
		shift -= 8;
	}
}

void des_destroy_block(uint8_t* data, const uint64_t* block) {
	uint8_t shift = 56;
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = (uint8_t)(*block >> shift);
		shift -= 8;
	}
}

uint32_t des_left_rotate_subkey(const uint32_t key, const uint8_t rotate) {
	uint32_t result = 0;
	uint32_t tmp_key = key;

	for (uint8_t i = 0; i < rotate; i++) {
		uint8_t tmp_bit = ((tmp_key & ((uint32_t)1 << 27)) >> 27);
		result = (((tmp_key << 1)) | tmp_bit) & 0x0FFFFFFF;
		tmp_key = result;
	}

	return result;
}

void des_generate_keys(const uint64_t key, uint64_t keys[]) {
	uint64_t compressed_key = des_perform_permutation(key, des_pc_1, 64, 56);
	uint32_t c_key = KEY_LOWER_HALF(compressed_key);
	uint32_t d_key = KEY_UPPER_HALF(compressed_key);

	for (uint8_t i = 0; i < 16; i++) {
		c_key = des_left_rotate_subkey(c_key, FLASH_ACCESS(des_key_shift[i]));
		d_key = des_left_rotate_subkey(d_key, FLASH_ACCESS(des_key_shift[i]));
		uint64_t new_key = ((uint64_t)(c_key) << 28) | d_key;

		keys[i] = des_perform_permutation(new_key, des_pc_2, 56, 48);
	}
}


void des_init(des_context_t* context) {
	des_generate_keys(context->user_key, context->expanded_key);
}

uint64_t des_encrypt_block(const des_context_t* context, const uint64_t block) {
	uint64_t permutated_data = des_perform_permutation(block, des_ip, 64, 64);

	uint32_t l_block = DATA_UPPER_HALF(permutated_data);
	uint32_t r_block = DATA_LOWER_HALF(permutated_data);

	for (uint8_t i = 0; i < 16; i++) {
		uint32_t tmp = l_block;
		l_block = r_block;
		r_block = tmp ^ des_f(r_block, context->expanded_key[i]);
	}

	// combine R + L
	uint64_t result = ((uint64_t)(r_block) << 32) | l_block;
	result = des_perform_permutation(result, des_inv_ip, 64, 64);

	return result;
}

void des_encrypt(const des_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		des_create_block(&data[i], &block);
		block = des_encrypt_block(context, block);
		des_destroy_block(&data[i], &block);
	}
}

uint64_t des_decrypt_block(const des_context_t* context, const uint64_t block) {
	uint64_t permutated_data = des_perform_permutation(block, des_ip, 64, 64);

	uint32_t l_block = DATA_UPPER_HALF(permutated_data);
	uint32_t r_block = DATA_LOWER_HALF(permutated_data);

	for (uint8_t i = 0; i < 16; i++) {
		uint32_t tmp = l_block;
		l_block = r_block;
		r_block = tmp ^ des_f(r_block, context->expanded_key[15 - i]);
	}

	// combine R + L
	uint64_t result = ((uint64_t)(r_block) << 32) | l_block;
	result = des_perform_permutation(result, des_inv_ip, 64, 64);

	return result;
}

void des_decrypt(const des_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 8) {
		uint64_t block = 0;
		des_create_block(&data[i], &block);
		block = des_decrypt_block(context, block);
		des_destroy_block(&data[i], &block);
	}
}
