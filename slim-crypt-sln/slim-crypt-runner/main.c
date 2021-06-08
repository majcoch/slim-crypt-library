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
		message_id msg_id = await_message();
		switch (msg_id) {
			case EXEC_ALGO_CMD:
				execution_status.status = 0;
				
				count_result.count = 
				eval[execute_algorithm_cmd.algorithm_code - 1][execute_algorithm_cmd.operation_code - 1]
				(data_transfer.data_buff, data_transfer.data_len);
				
				execution_status.status = 1;
				send_message(EXEC_STATUS, EXEC_STATUS_SIZE);
				break;
			
			case SEND_DATA_CMD:
				send_message(DATA_TRANSFER, DATA_TRANSFER_SIZE(data_transfer.data_len));
				break;
		
			case SEND_CNT_CMD:
				send_message(COUNT_RESULT, COUNT_RESULT_SIZE);
				break;
			
			default:
				// Invalid message received - do nothing
				break;
		}
	}
}
