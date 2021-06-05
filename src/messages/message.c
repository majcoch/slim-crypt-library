/*
 * message.c
 *
 * Created: 01.06.2021 12:24:25
 *  Author: Micha³ Granda
 */ 
#include "message.h"

size_t get_message_size(message_id msg_id){
	switch (msg_id) {
		case MSG_1: return sizeof(data_message_t);
		case MSG_2: return sizeof(request_message_t);
		case MSG_3: return sizeof(result_message_t);
		default:	return 0;
	}
}