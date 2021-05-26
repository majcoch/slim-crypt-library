/*
 * des_common.c
 *
 * Created: 26.05.2021 14:40:21
 *  Author: Micha³ Granda
 */ 
#include "des_common.h"

#include "../../data/des_data.h"

uint64_t perform_permutation(const uint64_t data, const uint8_t* tab, const uint8_t in_bits, const uint8_t out_bits) {
	uint64_t result = 0;

	for (uint8_t i = 0; i < out_bits; i++) {
		uint64_t mask = ((uint64_t)1 << (in_bits - tab[i]));
		result |= (((data & mask) >> (in_bits - tab[i])) << (out_bits - i - 1));
	}

	return result;
}

uint64_t f(const uint32_t r_block, const uint64_t key) {
	// Expand and XOR with key
	uint64_t permutated_block = perform_permutation(r_block, expand_table, 32, 48);
	permutated_block ^= key;

	// Apply s-box
	uint64_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		uint8_t bit_box = (permutated_block >> ((7 - i) * 6)) & 0b111111;

		uint8_t row = ((bit_box >> 4) & 0b000010) | (bit_box & 0b000001);
		uint8_t column = (bit_box & 0b011110) >> 1;

		uint8_t substitution = s_box[i][row][column];

		result |= ((uint64_t)(substitution) << ((7 - i) * 4));
	}

	result = perform_permutation(result, p, 32, 32);
	return result;
}

void create_block(const uint8_t* data, uint64_t* block) {
	uint8_t shift = 56;
	*block = 0;
	for (uint8_t i = 0; i < 8; i++) {
		*block |= (uint64_t)(data[i]) << shift;
		shift -= 8;
	}
}

void destroy_block(uint8_t* data, const uint64_t* block) {
	uint8_t shift = 56;
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = (uint8_t)(*block >> shift);
		shift -= 8;
	}
}
