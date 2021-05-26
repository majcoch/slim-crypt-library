/*
 * aes_init.c
 *
 * Created: 26.05.2021 11:18:31
 *  Author:  Micha³ Granda
 */ 
#include "aes_init.h"

#include <string.h>
#include "../../data/aes_data.h"

void aes_key_expand_core(uint8_t* key, const uint8_t iteration) {
	// Rotate left
	uint8_t tmp_byte = key[0];
	key[0] = key[1];
	key[1] = key[2];
	key[2] = key[3];
	key[3] = tmp_byte;

	// substitute with s_box
	key[0] = s_box[key[0]];
	key[1] = s_box[key[1]];
	key[2] = s_box[key[2]];
	key[3] = s_box[key[3]];

	key[0] ^= rcon[iteration];
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

void aes_init(aes_128_context_t* aes) {
	aes_expand_key(aes->user_key, aes->expanded_key);
}
