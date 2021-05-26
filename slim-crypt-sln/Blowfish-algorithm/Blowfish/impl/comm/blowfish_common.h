/*
 * blowfish_common.h
 *
 * Created: 26.05.2021 15:58:40
 *  Author: Micha³ Granda
 */ 


#ifndef BLOWFISH_COMMON_H_
#define BLOWFISH_COMMON_H_

#include <stdint.h>

uint32_t f(uint32_t x);

void create_block(const uint8_t* data, uint64_t* block);

void destroy_block(uint8_t* data, const uint64_t* block);

#endif /* BLOWFISH_COMMON_H_ */