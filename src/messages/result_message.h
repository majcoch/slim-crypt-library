/*
 * result_message.h
 *
 * Created: 31.05.2021 14:38:43
 *  Author: Micha³ Granda
 */ 


#ifndef RESULT_MESSAGE_H_
#define RESULT_MESSAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RESP_MSG_SIZE (sizeof(result_message_t))

typedef struct {
	uint32_t cycle_count;
} result_message_t;

#ifdef __cplusplus
}
#endif

#endif /* RESULT_MESSAGE_H_ */