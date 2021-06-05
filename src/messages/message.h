/*
 * message.h
 *
 * Created: 01.06.2021 12:09:10
 *  Author: Micha³ Granda
 */ 


#ifndef MESSAGE_H_
#define MESSAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include "data_message.h"
#include "result_message.h"
#include "request_message.h"

typedef enum {
	MSG_1 = 0x01,
	MSG_2 = 0x02,
	MSG_3 = 0x03
} message_id;

size_t get_message_size(message_id msg_id);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGE_H_ */