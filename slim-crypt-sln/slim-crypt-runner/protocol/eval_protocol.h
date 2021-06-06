/*
 * eval_protocol.h
 *
 * Created: 06.06.2021 09:44:13
 *  Author: Micha³ Granda
 */ 


#ifndef EVAL_PROTOCOL_H_
#define EVAL_PROTOCOL_H_

#include "uart/uart.h"
#include "serializer/msg_serializer.h"

// Callbacks table to process incoming messages
extern void (*serialize_msg[])(void(*)(uint8_t*, const size_t), uint16_t);

typedef enum {
	INVALID	 = 0x00,
	DATA_MSG = 0x01,
	REQU_MSG = 0x02,
	RESP_MSG = 0x03
} message_id;

// Protocol functions
message_id await_message(void);
void send_message(const message_id msg_id, const uint16_t msg_size);

#endif /* EVAL_PROTOCOL_H_ */