/*
 * context.h
 *
 * Created: 26.05.2021 12:22:06
 *  Author: Micha³ Granda
 */ 


#ifndef DES_CONTEXT_H_
#define DES_CONTEXT_H_

#include <stdint.h>

#define EXPA_KEY_LEN	16

typedef struct {
	uint64_t user_key;
	uint64_t expanded_key[EXPA_KEY_LEN];
} des_context_t;

#endif /* DES_CONTEXT_H_ */