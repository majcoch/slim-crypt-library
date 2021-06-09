/*
 * sha1_hash.h
 *
 * Created: 26.05.2021 16:28:42
 *  Author: Micha³ Granda
 */ 


#ifndef SHA1_HASH_H_
#define SHA1_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

void sha1_hash(uint8_t* message, const uint64_t len, uint32_t hash[5]);

#ifdef __cplusplus
}
#endif

#endif /* SHA1_HASH_H_ */