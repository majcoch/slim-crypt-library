/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Michał Granda
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart/uart.h"
#include "protocol/protocol.h"
#include "evaluation/evaluation.h"

// Array with evaluation functions
uint32_t (*eval[5][2])(uint8_t*, uint16_t) = {
	{sha1_hash_eval, NULL},
	{aes_enc_eval, aes_dec_eval},
	{des_enc_eval, des_dec_eval},
	{tea_enc_eval, tea_dec_eval},	
	{blowfish_enc_eval, blowfish_dec_eval}
};

// Communication protocol messages
data_message_t data_msg = { 0 };
request_message_t req_msg	= { 0 };
result_message_t res_msg = { 0 };

int main(void) {
	// Hardware initialization
	sei(); // Enable interrupts
	uart_init();
	
	// Encryption algorithms initialization
	aes_128_init(&aes);
	des_init(&des);
	
	// Evaluation loop
	while (1) {
		message_id id = wait_message();
		switch (id) {
			case MSG_1:
				get_message(&data_msg, MSG_1);
			break;
			
			case MSG_2:
				get_message(&req_msg, MSG_2);
				// Run evaluation of selected algorithm
				res_msg.cycle_count = eval[req_msg.alg - 1][req_msg.oper - 1](data_msg.data_buff, data_msg.data_len);
				// Send result data
				send_message(&data_msg, MSG_1);
				// Send cycle count measurement
				send_message(&res_msg, MSG_3);
			break;
		}
	}
}


