/*
 * des_dec.h
 *
 * Created: 26.05.2021 14:50:48
 *  Author: Micha³ Granda
 */ 


#ifndef DES_DEC_H_
#define DES_DEC_H_

#include <stdint.h>
#include <stddef.h>
#include "../des_context.h"

uint64_t des_decrypt_block(const des_context_t* context, const uint64_t block);

void des_decrypt(const des_context_t* context, uint8_t* data, const size_t len);

#endif /* DES_DEC_H_ */