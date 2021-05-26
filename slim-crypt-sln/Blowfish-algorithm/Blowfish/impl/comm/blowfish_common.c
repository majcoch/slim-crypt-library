/*
 * blowfish_common.c
 *
 * Created: 26.05.2021 15:58:55
 *  Author: Micha³ Granda
 */ 
#include "blowfish_common.h"

#include "../../data/blowfish_data.h"

uint32_t f(uint32_t x) {
	uint32_t h = blowfish_s_box[0][x >> 24] + blowfish_s_box[1][x >> 16 & 0xff];
	return (h ^ blowfish_s_box[2][x >> 8 & 0xff]) + blowfish_s_box[3][x & 0xff];
}

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
