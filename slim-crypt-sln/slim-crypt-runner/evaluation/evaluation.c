/*
 * evaluation.c
 *
 * Created: 05.06.2021 11:13:09
 *  Author: Micha³ Granda
 */ 
#include "evaluation.h"

#include <string.h>
#include "config/enc_config.h"
#include "measure.h"

uint32_t aes_enc_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	aes_128_encrypt(&aes, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t aes_dec_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	aes_128_decrypt(&aes, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t des_enc_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	des_encrypt(&des, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t des_dec_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	des_decrypt(&des, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t tea_enc_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	tea_encrypt(&tea, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t tea_dec_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	tea_decrypt(&tea, data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t blowfish_enc_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	blowfish_encrypt(data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t blowfish_dec_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	cycle_count_start();
	blowfish_decrypt(data, *size);
	cycle_count_stop();
	
	return cycle_count_get();
}

uint32_t sha1_hash_eval(uint8_t* data, uint16_t* size) {
	cycle_count_reset();
	
	uint32_t hash[5] = { 0 };
	
	cycle_count_start();
	sha1_hash(data, *size, hash);
	cycle_count_stop();
	
	memcpy(data, hash, 5 * sizeof(uint32_t));
	*size = 5 * sizeof(uint32_t);
	
	return cycle_count_get();
}
