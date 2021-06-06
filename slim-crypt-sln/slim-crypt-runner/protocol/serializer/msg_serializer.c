/*
 * msg_serializer.c
 *
 * Created: 06.06.2021 10:20:53
 *  Author: Micha³ Granda
 */ 
#include "msg_serializer.h"

// Messages
data_message_t data_msg = { 0 };
request_message_t req_msg	= { 0 };
result_message_t res_msg = { 0 };
	
void serialize_data_msg(void(*store)(uint8_t*, const size_t), uint16_t len) {
	store((uint8_t*)&data_msg.data_len, sizeof(uint16_t));
	store(data_msg.data_buff, len - sizeof(uint16_t));
}

void serialize_requ_msg(void(*store)(uint8_t*, const size_t), uint16_t len) {
	store((uint8_t*)&req_msg, len);
}

void serialize_resp_msg(void(*store)(uint8_t*, const size_t), uint16_t len) {
	store((uint8_t*)&res_msg, len);
}
