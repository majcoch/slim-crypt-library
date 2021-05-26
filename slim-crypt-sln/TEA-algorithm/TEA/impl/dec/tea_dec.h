/*
 * tea_dec.h
 *
 * Created: 26.05.2021 15:37:56
 *  Author: Micha³ Granda
 */ 


#ifndef TEA_DEC_H_
#define TEA_DEC_H_

#include <stdint.h>
#include <stddef.h>
#include "../tea_context.h"

uint64_t tea_decrypt_block(const tea_context_t* context, uint64_t block);

void tea_decrypt(const tea_context_t* context, uint8_t* data, const size_t len);

#endif /* TEA_DEC_H_ */