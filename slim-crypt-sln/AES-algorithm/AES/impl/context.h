/*
 * context.h
 *
 * Created: 26.05.2021 11:20:58
 *  Author: Micha³ Granda
 */ 


#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdint.h>

#define USER_KEY_LEN	16
#define EXPA_KEY_LEN	176

typedef struct {
	uint8_t user_key[USER_KEY_LEN];
	uint8_t expanded_key[EXPA_KEY_LEN];
}aes_128_context_t;


#endif /* CONTEXT_H_ */
