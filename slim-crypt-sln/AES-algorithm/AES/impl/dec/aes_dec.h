/*
 * aes_dec.h
 *
 * Created: 26.05.2021 11:19:31
 *  Author: Micha³ Granda
 */ 


#ifndef AES_DEC_H_
#define AES_DEC_H_

#include <stdint.h>
#include <stddef.h>
#include "../context.h"

void aes_128_decrypt_block(const aes_128_context_t* context, uint8_t* block);

void aes_128_decrypt(const aes_128_context_t* context, uint8_t* data, const size_t len);

#endif /* AES_DEC_H_ */