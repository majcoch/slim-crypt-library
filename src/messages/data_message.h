/*
 * data_message.h
 *
 * Created: 31.05.2021 14:38:20
 *  Author: Micha³ Granda
 */ 


#ifndef DATA_MESSAGE_H_
#define DATA_MESSAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint16_t data_len;
	uint8_t data_buff[32];
} data_message_t;

#ifdef __cplusplus
}
#endif

#endif /* DATA_MESSAGE_H_ */