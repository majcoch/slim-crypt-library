/*
 * tea.h
 *
 * Created: 26.05.2021 15:15:44
 *  Author: Micha³ Granda
 */ 


#ifndef TEA_H_
#define TEA_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint32_t user_key[4];
} tea_context_t;

uint64_t tea_encrypt_block(const tea_context_t* context, uint64_t block);

void tea_encrypt(const tea_context_t* context, uint8_t* data, const size_t len);

uint64_t tea_decrypt_block(const tea_context_t* context, uint64_t block);

void tea_decrypt(const tea_context_t* context, uint8_t* data, const size_t len);


#endif /* TEA_H_ */