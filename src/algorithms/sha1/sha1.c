/*
 * sha1_hash.c
 *
 * Created: 26.05.2021 16:28:50
 *  Author: Micha³ Granda
 */ 
#include "sha1.h"

#include <string.h>

#define H0_INIT 0x67452301
#define H1_INIT 0xEFCDAB89
#define H2_INIT 0x98BADCFE
#define H3_INIT 0x10325476
#define H4_INIT 0xC3D2E1F0

void store_big_endian_32_bits(uint32_t* dest, const uint8_t* src) {
	*dest |= (uint32_t)(src[0]) << 24;
	*dest |= (uint32_t)(src[1]) << 16;
	*dest |= (uint32_t)(src[2]) << 8;
	*dest |= (uint32_t)(src[3]);
}

void store_big_endian_64_bits(uint8_t* dest, const uint64_t* src) {
	uint8_t shift = 56;
	for (uint8_t i = 0; i < 8; i++) {
		dest[i] = (uint8_t)((*src * 8) >> shift);
		shift -= 8;
	}
}

uint32_t sha1_left_rotate(uint32_t value, uint8_t count) {
	return (value << count) | (value >> (32 - count));
}

void sha1_initialize_words(const uint8_t* block, uint32_t* words, uint16_t count) {
	uint8_t left = count % 4;
	uint8_t whole = count / 4;

	// process whole 4-byte-long chunks
	uint8_t processed;
	for (processed = 0; processed < whole; processed++) {
		store_big_endian_32_bits(&words[processed], &block[processed * 4]);
	}

	// process whats left
	uint8_t shift = 24;
	for (uint8_t i = 0; i < left; i++) {
		words[processed] |= ((uint32_t)(block[processed * 4 + i]) << shift);
		shift -= 8;
	}
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
		block[i] = sha1_left_rotate((block[i - 3] ^ block[i - 8] ^ block[i - 14] ^ block[i - 16]), 1);
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

		tmp = sha1_left_rotate(a, 5) + f + e + k + block[i];
		e = d;
		d = c;
		c = sha1_left_rotate(b, 30);
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

void sha1_hash(uint8_t* message, const uint64_t len, uint32_t hash[5]) {
	// Initialize hash value
	hash[0] = H0_INIT;
	hash[1] = H1_INIT;
	hash[2] = H2_INIT;
	hash[3] = H3_INIT;
	hash[4] = H4_INIT;

	// Append 1 bit to message
	message[len] = 0x80;

	// Calculate number of blocks to be processed
	uint64_t message_bits_ext = (len << 3) + 1;
	uint64_t message_bytes_ext = len + 1;
	uint64_t blocks_count = ((message_bits_ext + 64) >> 9) + 1;	// number of blocks that needs to be hashed

	// Process blocks
	for (uint64_t block = 0; block < blocks_count; block++) {
		uint32_t words[80] = { 0 };

		// Whole message fits into 448 bits
		if (message_bits_ext <= 448) {
			uint8_t last_block[64] = { 0 };
			memcpy(last_block, &message[64 * block], message_bytes_ext * sizeof(uint8_t));
			// Append message size
			store_big_endian_64_bits(&last_block[56], &len);
			// Generate words
			sha1_initialize_words(last_block, words, 64);
		}
		// Process whole block
		else {
			// Generate words
			uint8_t bytes_to_process = message_bytes_ext < 64 ? message_bytes_ext : 64;
			sha1_initialize_words(&message[(block * 64)], words, bytes_to_process);

			message_bytes_ext -= bytes_to_process;
			message_bits_ext -= message_bits_ext < 512 ? message_bits_ext : 512;
		}

		sha1_hash_block(words, hash);
	}

}
