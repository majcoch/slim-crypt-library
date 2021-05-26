/*
 * common.h
 *
 * Created: 26.05.2021 14:39:57
 *  Author: Micha³ Granda
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#define DATA_UPPER_HALF(x) (uint32_t)(x >> 32)
#define DATA_LOWER_HALF(x) (uint32_t)(x)

uint64_t perform_permutation(const uint64_t data, const uint8_t* tab, const uint8_t in_bits, const uint8_t out_bits);

uint64_t f(const uint32_t r_block, const uint64_t key);

void create_block(const uint8_t* data, uint64_t* block);

void destroy_block(uint8_t* data, const uint64_t* block);

#endif /* COMMON_H_ */
