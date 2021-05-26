/*
 * blowfish_dec.h
 *
 * Created: 26.05.2021 16:16:49
 *  Author: Micha³ Granda
 */ 


#ifndef BLOWFISH_DEC_H_
#define BLOWFISH_DEC_H_

#include <stdint.h>
#include <stddef.h>

uint64_t blowfish_decrypt_block(uint64_t block);

void blowfish_decrypt(uint8_t* data, const size_t len);

#endif /* BLOWFISH_DEC_H_ */