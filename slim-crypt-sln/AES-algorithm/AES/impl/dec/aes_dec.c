/*
 * aes_dec.c
 *
 * Created: 26.05.2021 11:19:41
 *  Author: Micha³ Granda
 */ 
#include "aes_dec.h"

#include "../../data/aes_data.h"
#include "../comm/aes_comm.h"

void aes_inv_sub_bytes(uint8_t* state) {
	for (uint8_t i = 0; i < 16; i++)
	state[i] = inv_s_box[state[i]];
}

void aes_inv_shift_rows(uint8_t* state) {
	uint8_t tmp = 0;

	tmp = state[3];
	state[3] = state[7];
	state[7] = state[11];
	state[11] = state[15];
	state[15] = tmp;

	tmp = state[2];
	state[2] = state[10];
	state[10] = tmp;
	tmp = state[6];
	state[6] = state[14];
	state[14] = tmp;

	tmp = state[1];
	state[1] = state[13];
	state[13] = state[9];
	state[9] = state[5];
	state[5] = tmp;
}

void aes_inv_mix_columns(uint8_t* state) {
	uint8_t i = 4;
	uint8_t tmp_column[4];

	while (i--) {
		uint8_t offset = 4 * i;
		tmp_column[0] = aes_galois_multiply(14, state[offset]) ^ aes_galois_multiply(11, state[offset + 1]) ^ aes_galois_multiply(13, state[offset + 2]) ^ aes_galois_multiply(9, state[offset + 3]);
		tmp_column[1] = aes_galois_multiply(9, state[offset]) ^ aes_galois_multiply(14, state[offset + 1]) ^ aes_galois_multiply(11, state[offset + 2]) ^ aes_galois_multiply(13, state[offset + 3]);
		tmp_column[2] = aes_galois_multiply(13, state[offset]) ^ aes_galois_multiply(9, state[offset + 1]) ^ aes_galois_multiply(14, state[offset + 2]) ^ aes_galois_multiply(11, state[offset + 3]);
		tmp_column[3] = aes_galois_multiply(11, state[offset]) ^ aes_galois_multiply(13, state[offset + 1]) ^ aes_galois_multiply(9, state[offset + 2]) ^ aes_galois_multiply(14, state[offset + 3]);

		state[offset] = tmp_column[0];
		state[offset + 1] = tmp_column[1];
		state[offset + 2] = tmp_column[2];
		state[offset + 3] = tmp_column[3];
	}
}


void aes_128_decrypt_block(const aes_128_context_t* context, uint8_t* block) {
	const uint8_t* exp_keys = context->expanded_key;
	uint8_t rounds_count = AES_128_ROUNDS_CNT + 1;

	aes_add_round_key(block, exp_keys + (rounds_count << 4));

	for (uint8_t i = 1; i < rounds_count; i++) {
		aes_inv_shift_rows(block);
		aes_inv_sub_bytes(block);
		aes_add_round_key(block, exp_keys + ((rounds_count - i) << 4));
		aes_inv_mix_columns(block);
	}

	aes_inv_shift_rows(block);
	aes_inv_sub_bytes(block);
	aes_add_round_key(block, exp_keys);
}

void aes_128_decrypt(const aes_128_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 16) {
		aes_128_decrypt_block(context, &data[i]);
	}
}
