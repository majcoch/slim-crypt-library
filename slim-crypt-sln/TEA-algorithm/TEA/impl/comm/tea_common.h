/*
 * tea_common.h
 *
 * Created: 26.05.2021 15:20:16
 *  Author: Micha³ Granda
 */ 


#ifndef TEA_COMMON_H_
#define TEA_COMMON_H_

#include <stdint.h>

#define MAGIC_CONSTANT	(uint32_t)(0x9E3779B9)
#define ENCRYPT_SUM		(uint32_t)(0x00000000)
#define DECRYPT_SUM		(uint32_t)(MAGIC_CONSTANT * (uint32_t)0x20)	//  0xC6EF3720

void create_block(const uint8_t* data, uint64_t* block);

void destroy_block(uint8_t* data, const uint64_t* block);

#endif /* TEA_COMMON_H_ */
