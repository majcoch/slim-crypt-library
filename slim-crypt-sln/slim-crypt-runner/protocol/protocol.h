/*
 * protocol.h
 *
 * Created: 31.05.2021 14:11:51
 *  Author: Micha³ Granda
 */ 


#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>
#include <stddef.h>

#include "messages/message.h"

// Blocks execution until any message is received
// returns message ID
message_id wait_message( void );

// Sends message 
void send_message(void* msg, message_id msg_id);

// Serializes message from input buffer
void get_message(void* msg, message_id msg_id);

#endif /* PROTOCOL_H_ */