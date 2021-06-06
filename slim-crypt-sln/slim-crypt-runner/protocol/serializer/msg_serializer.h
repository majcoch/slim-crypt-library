/*
 * msg_serializer.h
 *
 * Created: 06.06.2021 10:20:49
 *  Author: Micha³ Granda
 */ 


#ifndef MSG_SERIALIZER_H_
#define MSG_SERIALIZER_H_

#include <stdint.h>
#include <stddef.h>

#include "messages/data_message.h"
#include "messages/result_message.h"
#include "messages/request_message.h"

// Static messages declarations
extern data_message_t data_msg;
extern request_message_t req_msg;
extern result_message_t res_msg;

void serialize_data_msg(void(*store)(uint8_t*, const size_t), uint16_t len);

void serialize_requ_msg(void(*store)(uint8_t*, const size_t), uint16_t len);

void serialize_resp_msg(void(*store)(uint8_t*, const size_t), uint16_t len);

#endif /* MSG_SERIALIZER_H_ */