/*
 * protocol.c
 *
 * Created: 31.05.2021 14:13:50
 *  Author: Micha³ Granda
 */ 
#include "protocol.h"

#include <string.h>
#include "../uart/uart.h"

// Transmission buffer used to serialize incoming packets
uint8_t transmission_buffer[64] = { 0 };

message_id wait_message(void) {
	// ID LAYER
	uint8_t msg_id = 0;
	uart_read_byte(&msg_id);
	
	// SIZE LAYER - read 2 bytes
	uint16_t msg_size = 0;
	uart_read(transmission_buffer, sizeof(uint16_t));
	memcpy(&msg_size, transmission_buffer, sizeof(uint16_t));
	
	// PAYLOAD LAYER
	uart_read(transmission_buffer, msg_size * sizeof(uint8_t));
	// At this point whole message is inside transmission_buffer
	// and can be easily serialized and deserialized
	
	// Send back response that message has been received
	uart_write_byte(0xAA);
	
	return (message_id)msg_id;
}

void send_message(void* msg, message_id msg_id) {
	memset(transmission_buffer, 0, 64);
	// ID LAYER
	transmission_buffer[0] = (uint8_t)msg_id;
	
	// SIZE LAYER - read 2 bytes
	uint16_t msg_size = get_message_size(msg_id);
	memcpy(&transmission_buffer[1], &msg_size, sizeof(uint16_t));
	
	// PAYLOAD LAYER
	memcpy(&transmission_buffer[3], msg, get_message_size(msg_id));
	
	uart_write(transmission_buffer, 3 + msg_size);
	
	// Wait for ACK
	uint8_t resp = 0;
	while(resp != 0xAA) uart_read_byte(&resp);
}

void get_message(void* msg, message_id msg_id) {
	memcpy(msg, transmission_buffer, get_message_size(msg_id));
}
