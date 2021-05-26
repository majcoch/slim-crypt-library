/*
 * tea_context.h
 *
 * Created: 26.05.2021 15:19:04
 *  Author: Micha³ Granda
 */ 


#ifndef TEA_CONTEXT_H_
#define TEA_CONTEXT_H_

#include <stdint.h>

typedef struct {
	uint32_t user_key[4];
} tea_context_t;

#endif /* TEA_CONTEXT_H_ */
