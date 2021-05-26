/*
 * aes.c
 *
 * Created: 26.05.2021 19:08:52
 *  Author: Micha³ Granda
 */ 
#include "aes.h"

#include <string.h>
#include "data/aes_data.h"

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

void aes_key_expand_core(uint8_t* key, const uint8_t iteration) {
	// Rotate left
	uint8_t tmp_byte = key[0];
	key[0] = key[1];
	key[1] = key[2];
	key[2] = key[3];
	key[3] = tmp_byte;

	// substitute with s_box
	key[0] = aes_s_box[key[0]];
	key[1] = aes_s_box[key[1]];
	key[2] = aes_s_box[key[2]];
	key[3] = aes_s_box[key[3]];

	key[0] ^= aes_rcon[iteration];
}

void aes_expand_key(const uint8_t* user_key, uint8_t* exp_key) {
	memcpy(exp_key, user_key, 16 * sizeof(uint8_t));

	uint8_t tmp_core[4] = { 0 };
	uint8_t rcon_iter = 1;
	for (uint8_t i = 16; i < 176; i += 4) {
		memcpy(tmp_core, &exp_key[i - 4], 4 * sizeof(uint8_t));

		if (0 == (i % 16)) {
			aes_key_expand_core(tmp_core, rcon_iter++);
		}

		for (uint8_t j = 0; j < 4; j++) {
			exp_key[i + j] = exp_key[i + j - 16] ^ tmp_core[j];
		}
	}
}

void aes_sub_bytes(uint8_t* state) {
	for (uint8_t i = 0; i < 16; i++){
		state[i] = aes_s_box[state[i]];
	}
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

void aes_inv_sub_bytes(uint8_t* state) {
	for (uint8_t i = 0; i < 16; i++){
		state[i] = aes_inv_s_box[state[i]];
	}
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


void aes_init(aes_128_context_t* aes) {
	aes_expand_key(aes->user_key, aes->expanded_key);
}

void aes_128_encrypt_block(const aes_128_context_t* context, uint8_t* block) {
	const uint8_t* exp_keys = context->expanded_key;

	aes_add_round_key((uint8_t*)block, (uint8_t*)exp_keys);

	for (int i = 0; i < 9; i++) {
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

void aes_128_decrypt_block(const aes_128_context_t* context, uint8_t* block) {
	const uint8_t* exp_keys = context->expanded_key;
	uint8_t rounds_count = 10;

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
