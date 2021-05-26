/*
 * aes_enc.h
 *
 * Created: 26.05.2021 11:19:02
 *  Author: Micha³ Granda
 */ 


#ifndef AES_ENC_H_
#define AES_ENC_H_

#include <stdint.h>
#include <stddef.h>
#include "../context.h"

void aes_128_encrypt_block(const aes_128_context_t* context, uint8_t* block);

void aes_128_encrypt(const aes_128_context_t* context, uint8_t* data, const size_t len);

#endif /* AES_ENC_H_ */