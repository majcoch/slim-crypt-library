/*
 * commands.h
 *
 * Created: 08.06.2021 12:01:05
 *  Author: Micha³ Granda
 */ 


#ifndef COMMANDS_H_
#define COMMANDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint8_t algorithm_code;
	uint8_t operation_code;
} execute_algorithm_cmd_m;
#define EXEC_ALGO_CMD_SIZE sizeof(execute_algorithm_cmd_m)

typedef enum {
	SHA_1 = 0x01,
	AES	 = 0x02,
	DES = 0x03,
	TEA = 0x04,
	BLOWFISH = 0x05
} algorithm_e;

typedef enum {
	ENCRYPTION = 0x01,
	DECRYPTION = 0x02
} operation_e;

typedef struct { } send_data_cmd_m;

typedef struct { } send_count_cmd_m;

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_H_ */