/*
 * des.h
 *
 * Created: 26.05.2021 12:15:42
 *  Author: Micha³ Granda
 */ 


#ifndef DES_H_
#define DES_H_

#include <stdint.h>
#include <stddef.h>

#define DES_EXPA_KEY_LEN	16

typedef struct {
	uint64_t user_key;
	uint64_t expanded_key[DES_EXPA_KEY_LEN];
} des_context_t;

void des_init(des_context_t* context);

uint64_t des_encrypt_block(const des_context_t* context, const uint64_t block);

void des_encrypt(const des_context_t* context, uint8_t* data, const size_t len);

uint64_t des_decrypt_block(const des_context_t* context, const uint64_t block);

void des_decrypt(const des_context_t* context, uint8_t* data, const size_t len);

#endif /* DES_H_ */