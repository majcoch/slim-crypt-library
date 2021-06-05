/*
 * request_message.h
 *
 * Created: 31.05.2021 14:38:36
 *  Author: Micha³ Granda
 */ 


#ifndef REQUEST_MESSAGE_H_
#define REQUEST_MESSAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
	SHA1 = 0x01,
	AES = 0x02,
	DES = 0x03,
	TEA = 0x04,
	BLOWFISH = 0x05
} encryption_algorithm;

typedef enum {
	ENCRYPT = 0x01,
	DECRYPT = 0x02
} encryption_operation;

typedef struct {
	uint8_t alg;
	uint8_t oper;
} request_message_t;

#ifdef __cplusplus
}
#endif

#endif /* REQUEST_MESSAGE_H_ */