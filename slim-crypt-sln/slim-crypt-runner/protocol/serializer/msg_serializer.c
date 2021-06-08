/*
 * msg_serializer.c
 *
 * Created: 06.06.2021 10:20:53
 *  Author: Micha³ Granda
 */ 
#include "msg_serializer.h"

// Static messages declarations
execute_algorithm_cmd_m execute_algorithm_cmd = { 0 };
send_data_cmd_m send_data_command;
send_count_cmd_m send_count_command;
execution_status_m execution_status = { 0 };
count_result_m count_result = { 0 };
data_transfer_m data_transfer = { 0 };

void serialize_execute_algorithm_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	store(&execute_algorithm_cmd.algorithm_code, sizeof(uint8_t));
	store(&execute_algorithm_cmd.operation_code, sizeof(uint8_t));
}

void serialize_send_data_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	
}

void serialize_send_count_cmd(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	
}

void serialize_execution_status(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	store((uint8_t*)&execution_status.status, len);
}

void serialize_count_result(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	store((uint8_t*)&count_result.count, len);
}

void serialize_data_transfer(void(*store)(uint8_t*, const size_t), const uint16_t len) {
	store((uint8_t*)&data_transfer.data_len, sizeof(uint16_t));
	store(data_transfer.data_buff, len - sizeof(uint16_t));
}
