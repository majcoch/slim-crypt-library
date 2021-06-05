/*
 * sha1_hash.c
 *
 * Created: 26.05.2021 16:28:50
 *  Author: Micha³ Granda
 */ 
#include "sha1.h"

#include <string.h>
#include "data/sha1_data.h"

#ifdef __AVR__
	#include <avr/pgmspace.h>
	#define FLASH_ACCESS(x) pgm_read_byte(&(x))
#else
	#define FLASH_ACCESS(x) (x)
#endif // __AVR__


void store_big_endian(uint32_t* dest, uint8_t* src) {
	*dest |= (uint32_t)(src[0]) << 24;
	*dest |= (uint32_t)(src[1]) << 16;
	*dest |= (uint32_t)(src[2]) << 8;
	*dest |= (uint32_t)(src[3]);
}

uint32_t left_rotate(uint32_t value, uint8_t count) {
	return (value << count) | (value >> (32 - count));
}

void sha1_hash_block(uint32_t* block, uint32_t* current_hash) {
	// Initialize values for current block
	uint32_t a = current_hash[0],
	b = current_hash[1],
	c = current_hash[2],
	d = current_hash[3],
	e = current_hash[4];

	// Extend
	for (uint8_t i = 16; i < 80; i++) {
		block[i] = left_rotate((block[i - 3] ^ block[i - 8] ^ block[i - 14] ^ block[i - 16]), 1);
	}

	// Hash
	for (uint8_t i = 0; i < 80; i++) {
		uint32_t f = 0;
		uint32_t k = 0;
		uint32_t tmp = 0;
		if (i >= 0 && i <= 19) {
			f = (b & c) | ((~b) & d);
			k = 0x5A827999;
		}
		else if (i >= 20 && i <= 39) {
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		}
		else if (i >= 40 && i <= 59) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		}
		else if (i >= 60 && i <= 79) {
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		tmp = left_rotate(a, 5) + f + e + k + block[i];
		e = d;
		d = c;
		c = left_rotate(b, 30);
		b = a;
		a = tmp;
	}

	// Update current hash values
	current_hash[0] += a;
	current_hash[1] += b;
	current_hash[2] += c;
	current_hash[3] += d;
	current_hash[4] += e;
}

void sha1_hash(uint8_t* message, uint64_t len, uint32_t hash[]) {
	// Initialize hash value
	hash[0] = FLASH_ACCESS(sha1_h[0]);
	hash[1] = FLASH_ACCESS(sha1_h[1]);
	hash[2] = FLASH_ACCESS(sha1_h[2]);
	hash[3] = FLASH_ACCESS(sha1_h[3]);
	hash[4] = FLASH_ACCESS(sha1_h[4]);

	// Calculate number of blocks to be processed
	uint64_t bits_total = len + 64 + 1;
	uint64_t blocks = (bits_total / 512) + 1;

	// Process whole blocks
	for (uint64_t block = 0; block < blocks - 1; block++) {
		// Message schedule: extend the sixteen 32-bit words into eighty 32-bit words:
		uint32_t words[80] = { 0 };
		uint16_t cnt = 0;
		for (uint8_t i = 0; i < 16; i++) {
			store_big_endian(&words[i], &message[(block * 64) + cnt]);
			cnt += 4;
		}
		// Process block
		sha1_hash_block(words, hash);
	}

	// Process blocks of size < 448 bits
	uint8_t last_block[64] = { 0 };
	uint16_t bytes_left = (len / 8) - (64 * (blocks - 1));
	memcpy(last_block, &message[64 * (blocks - 1)], bytes_left * sizeof(uint8_t));
	// Append 1 bit to message
	last_block[bytes_left] = 0x80;
	// Append message size
	uint8_t shift = 56;
	for (uint8_t i = 0; i < 8; i++) {
		last_block[56 + i] = (uint8_t)(len >> shift);
		shift -= 8;
	}

	uint32_t words[80] = { 0 };
	uint16_t cnt = 0;
	for (uint8_t i = 0; i < 16; i++) {
		store_big_endian(&words[i], &last_block[cnt]);
		cnt += 4;
	}

	sha1_hash_block(words, hash);
}
