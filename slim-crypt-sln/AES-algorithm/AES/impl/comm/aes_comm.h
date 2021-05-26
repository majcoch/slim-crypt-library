/*
 * aes_comm.h
 *
 * Created: 26.05.2021 11:16:53
 *  Author: Micha³ Granda
 */ 


#ifndef AES_COMM_H_
#define AES_COMM_H_

#include <stdint.h>

void aes_add_round_key(uint8_t* state, const uint8_t* key);

uint8_t aes_galois_multiply(uint8_t a, uint8_t b);

#endif /* AES_COMM_H_ */