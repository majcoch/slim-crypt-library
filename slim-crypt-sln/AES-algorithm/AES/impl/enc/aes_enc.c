/*
 * aes_enc.c
 *
 * Created: 26.05.2021 11:19:13
 *  Author: Micha³ Granda
 */ 
#include "aes_enc.h"

#include "../../data/aes_data.h"
#include "../comm/aes_comm.h"


void aes_sub_bytes(uint8_t* state) {
	for (uint8_t i = 0; i < 16; i++)
	state[i] = s_box[state[i]];
}

void aes_shift_rows(uint8_t* state) {
	uint8_t tmp_element;

	// 2nd row shift - 1 byte shift
	tmp_element = state[1];
	state[1] = state[5];
	state[5] = state[9];
	state[9] = state[13];
	state[13] = tmp_element;

	// 3rd row shift - 2 byte shift swap pairs (2, 10) and (6 ,14)
	tmp_element = state[2];
	state[2] = state[10];
	state[10] = tmp_element;
	tmp_element = state[6];
	state[6] = state[14];
	state[14] = tmp_element;

	// 4th row shift
	tmp_element = state[3];
	state[3] = state[15];
	state[15] = state[11];
	state[11] = state[7];
	state[7] = tmp_element;
}

void aes_mix_columns(uint8_t* state) {
	uint8_t tmp_column[4] = { 0 };
	for (uint8_t offset = 0; offset < 16; offset += 4) {
		tmp_column[0] = (uint8_t)(aes_galois_multiply(2, state[offset]) ^ aes_galois_multiply(3, state[1 + offset]) ^ state[2 + offset] ^ state[3 + offset]);
		tmp_column[1] = (uint8_t)(state[offset] ^ aes_galois_multiply(2, state[1 + offset]) ^ aes_galois_multiply(3, state[2 + offset]) ^ state[3 + offset]);
		tmp_column[2] = (uint8_t)(state[offset] ^ state[1 + offset] ^ aes_galois_multiply(2, state[2 + offset]) ^ aes_galois_multiply(3, state[3 + offset]));
		tmp_column[3] = (uint8_t)(aes_galois_multiply(3, state[offset]) ^ state[1 + offset] ^ state[2 + offset] ^ aes_galois_multiply(2, state[3 + offset]));

		state[offset] = tmp_column[0];
		state[offset + 1] = tmp_column[1];
		state[offset + 2] = tmp_column[2];
		state[offset + 3] = tmp_column[3];
	}
}


void aes_128_encrypt_block(const aes_128_context_t* context, uint8_t* block) {
	const uint8_t* exp_keys = context->expanded_key;

	aes_add_round_key((uint8_t*)block, (uint8_t*)exp_keys);

	for (int i = 0; i < AES_128_ROUNDS_CNT; i++) {
		aes_sub_bytes((uint8_t*)block);
		aes_shift_rows((uint8_t*)block);
		aes_mix_columns((uint8_t*)block);
		aes_add_round_key((uint8_t*)block, (uint8_t*)exp_keys + (16 * (i + 1)));
	}

	aes_sub_bytes((uint8_t*)block);
	aes_shift_rows((uint8_t*)block);
	aes_add_round_key((uint8_t*)block, (uint8_t*)exp_keys + 160);
}

void aes_128_encrypt(const aes_128_context_t* context, uint8_t* data, const size_t len) {
	for (size_t i = 0; i < len; i += 16) {
		aes_128_encrypt_block(context, &data[i]);
	}
}
