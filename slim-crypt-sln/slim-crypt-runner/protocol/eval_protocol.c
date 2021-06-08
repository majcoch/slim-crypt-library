/*
 * eval_protocol.c
 *
 * Created: 06.06.2021 09:44:17
 *  Author: Micha³ Granda
 */ 
#include "eval_protocol.h"

// Callbacks
void (*serialize_msg[])(void(*)(uint8_t*, const size_t), const uint16_t) = {
	serialize_execute_algorithm_cmd,
	serialize_send_data_cmd,
	serialize_send_count_cmd,
	serialize_execution_status,
	serialize_count_result,
	serialize_data_transfer
};

message_id await_message() {
	uint8_t msg_id = 0;
	uint16_t msg_size = 0;
	
	// ID LAYER
	uart_read_byte(&msg_id);	// Hangs and waits for one byte of data
	
	// SIZE LAYER - read 2 bytes
	uart_read((uint8_t*)&msg_size, sizeof(uint16_t));	// Risky and memcpy would be better but works on AVR platform
	
	// PAYLOAD LAYER
	serialize_msg[msg_id - 1](uart_read, msg_size); // Dispatch message receiving to callback
	
	// Send ACK
	uart_write_byte(0xAA);
	
	return (message_id)msg_id;
}

void send_message(const message_id msg_id, const uint16_t msg_size) {
	// ID LAYER
	uart_write_byte((uint8_t)msg_id);
	
	// SIZE LAYER
	uart_write((uint8_t*)&msg_size, sizeof(uint16_t));
	
	// PAYLOAD LAYER
	serialize_msg[msg_id - 1](uart_write, msg_size); // Dispatch message sending to callback
	
	// Wait for ACK
	uint8_t resp = 0;
	while(resp != 0xAA) uart_read_byte(&resp);
}
