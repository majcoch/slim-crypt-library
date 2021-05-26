/*
 * tea_enc.h
 *
 * Created: 26.05.2021 15:21:01
 *  Author: Micha³ Granda
 */ 


#ifndef TEA_ENC_H_
#define TEA_ENC_H_

#include <stdint.h>
#include <stddef.h>
#include "../tea_context.h"

uint64_t tea_encrypt_block(const tea_context_t* context, uint64_t block);

void tea_encrypt(const tea_context_t* context, uint8_t* data, const size_t len);

#endif /* TEA_ENC_H_ */