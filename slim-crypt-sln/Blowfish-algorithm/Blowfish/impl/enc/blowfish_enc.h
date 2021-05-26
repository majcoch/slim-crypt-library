/*
 * blowfish_enc.h
 *
 * Created: 26.05.2021 15:51:33
 *  Author: Micha³ Granda
 */ 


#ifndef BLOWFISH_ENC_H_
#define BLOWFISH_ENC_H_

#include <stdint.h>
#include <stddef.h>

uint64_t blowfish_encrypt_block(uint64_t block);

void blowfish_encrypt(uint8_t* data, const size_t len);

#endif /* BLOWFISH_ENC_H_ */