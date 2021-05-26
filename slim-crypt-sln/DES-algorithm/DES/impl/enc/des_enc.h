/*
 * des_enc.h
 *
 * Created: 26.05.2021 14:50:41
 *  Author: Micha³ Granda
 */ 


#ifndef DES_ENC_H_
#define DES_ENC_H_

#include <stdint.h>
#include <stddef.h>
#include "../des_context.h"

uint64_t des_encrypt_block(const des_context_t* context, const uint64_t block);

void des_encrypt(const des_context_t* context, uint8_t* data, const size_t len);

#endif /* DES_ENC_H_ */