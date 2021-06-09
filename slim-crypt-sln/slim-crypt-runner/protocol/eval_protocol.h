/*
 * eval_protocol.h
 *
 * Created: 06.06.2021 09:44:13
 *  Author: Micha³ Granda
 */ 


#ifndef EVAL_PROTOCOL_H_
#define EVAL_PROTOCOL_H_

#include "uart/uart.h"
#include "messages/message_id.h"
#include "serializer/msg_serializer.h"

// Callbacks table to process incoming messages
extern void (*serialize_msg[])(void(*)(uint8_t*, const size_t), const uint16_t);

// Protocol functions
message_id await_message(void);
void send_message(const message_id msg_id, const uint16_t msg_size);

#endif /* EVAL_PROTOCOL_H_ */