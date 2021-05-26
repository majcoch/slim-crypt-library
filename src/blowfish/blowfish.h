/*
 * blowfish.h
 *
 * Created: 26.05.2021 15:45:27
 *  Author: Micha³ Granda
 */ 


#ifndef BLOWFISH_H_
#define BLOWFISH_H_

#include <stdint.h>
#include <stddef.h>

uint64_t blowfish_encrypt_block(uint64_t block);

void blowfish_encrypt(uint8_t* data, const size_t len);

uint64_t blowfish_decrypt_block(uint64_t block);

void blowfish_decrypt(uint8_t* data, const size_t len);

#endif /* BLOWFISH_H_ */