/*
 * message_id.h
 *
 * Created: 08.06.2021 13:07:32
 *  Author: Micha³ Granda
 */ 


#ifndef MESSAGE_ID_H_
#define MESSAGE_ID_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	INVALID	 = 0x00,
	// Commands
	EXEC_ALGO_CMD,	// Execute encryption algorithm
	SEND_DATA_CMD,	// Send data command
	SEND_CNT_CMD,	// Send encryption evaluation results
	// Responses
	EXEC_STATUS,	// Send after execution is completed
	COUNT_RESULT,	// Execution cycle measure
	// Data transfer
	DATA_TRANSFER,	// Data block transfer
} message_id;

#ifdef __cplusplus
}
#endif

#endif /* MESSAGE_ID_H_ */