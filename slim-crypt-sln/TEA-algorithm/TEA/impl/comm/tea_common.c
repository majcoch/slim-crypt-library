/*
 * tea_common.c
 *
 * Created: 26.05.2021 15:32:17
 *  Author: Micha³ Granda
 */ 
#include "tea_common.h"

void create_block(const uint8_t* data, uint64_t* block) {
	uint8_t shift = 56;
	*block = 0;
	for (uint8_t i = 0; i < 8; i++) {
		*block |= (uint64_t)(data[i]) << shift;
		shift -= 8;
	}
}

void destroy_block(uint8_t* data, const uint64_t* block) {
	uint8_t shift = 56;
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = (uint8_t)(*block >> shift);
		shift -= 8;
	}
}
