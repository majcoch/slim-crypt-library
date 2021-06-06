/*
 * slim-crypt-runner.c
 *
 * Created: 26.04.2021 10:28:00
 * Author : Michał Granda
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "protocol/eval_protocol.h"
#include "evaluation/evaluation.h"

// Lookup table with evaluation functions
uint32_t (*eval[5][2])(uint8_t*, uint16_t) = {
	{sha1_hash_eval, NULL},
	{aes_enc_eval, aes_dec_eval},
	{des_enc_eval, des_dec_eval},
	{tea_enc_eval, tea_dec_eval},
	{blowfish_enc_eval, blowfish_dec_eval}
};

int main(void) {
	// Hardware initialization
	sei();
	uart_init();
	
	// Encryption algorithms initialization
	aes_128_init(&aes);
	des_init(&des);
	
	while (1) {
		message_id id = await_message();
		switch ( id ) {
		case REQU_MSG:
			//// Run evaluation of selected algorithm
			res_msg.cycle_count = eval[req_msg.alg - 1][req_msg.oper - 1](data_msg.data_buff, data_msg.data_len);			
			send_message(DATA_MSG, DATA_MSG_SIZE(data_msg.data_len));
			// Send cycle count measurement
			send_message(RESP_MSG, RESP_MSG_SIZE);
		break;
		}
	}
}
