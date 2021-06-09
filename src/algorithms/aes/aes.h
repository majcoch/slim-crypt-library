/*
 * aes.h
 *
 * Created: 26.04.2021 11:20:25
 *  Author: Micha³ Granda
 */ 


#ifndef AES_H_
#define AES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#define AES_USER_KEY_LEN	16
#define AES_EXPA_KEY_LEN	176

typedef struct {
	uint8_t user_key[AES_USER_KEY_LEN];
	uint8_t expanded_key[AES_EXPA_KEY_LEN];
}aes_128_context_t;

void aes_128_init(aes_128_context_t* aes);

void aes_128_encrypt_block(const aes_128_context_t* context, uint8_t* block);

void aes_128_encrypt(const aes_128_context_t* context, uint8_t* data, const size_t len);

void aes_128_decrypt_block(const aes_128_context_t* context, uint8_t* block);

void aes_128_decrypt(const aes_128_context_t* context, uint8_t* data, const size_t len);


#ifdef __cplusplus
}
#endif

#endif /* AES_H_ */