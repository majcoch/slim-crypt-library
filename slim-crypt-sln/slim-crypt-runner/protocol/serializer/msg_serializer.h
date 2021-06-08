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

#include "messages/commands.h"
#include "messages/responses.h"
#include "messages/data_transfers.h"

extern execute_algorithm_cmd_m execute_algorithm_cmd;
extern send_data_cmd_m send_data_command;
extern send_count_cmd_m send_count_command;
extern execution_status_m execution_status;
extern count_result_m count_result;
extern data_transfer_m data_transfer;

void serialize_execute_algorithm_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len);

void serialize_send_data_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len);

void serialize_send_count_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len);

void serialize_execution_status(void(*store)(uint8_t*, const size_t), const uint16_t len);

void serialize_count_result(void(*store)(uint8_t*, const size_t), const uint16_t len);

void serialize_data_transfer(void(*store)(uint8_t*, const size_t), const uint16_t len);

#endif /* MSG_SERIALIZER_H_ */