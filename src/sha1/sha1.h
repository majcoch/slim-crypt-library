/*
 * sha1_hash.h
 *
 * Created: 26.05.2021 16:28:42
 *  Author: Micha³ Granda
 */ 


#ifndef SHA1_HASH_H_
#define SHA1_HASH_H_

#include <stdint.h>
#include <stddef.h>

void sha1_hash(uint8_t* message, uint64_t len, uint32_t hash[]);

#endif /* SHA1_HASH_H_ */