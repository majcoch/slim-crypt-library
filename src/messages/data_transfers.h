/*
 * data_transfers.h
 *
 * Created: 08.06.2021 12:01:33
 *  Author: Micha³ Granda
 */ 


#ifndef DATA_TRANSFERS_H_
#define DATA_TRANSFERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define BUFFER_SIZE 520

typedef struct {
	uint16_t data_len;
	uint8_t data_buff[BUFFER_SIZE];
} data_transfer_m;
#define DATA_TRANSFER_SIZE(x) (sizeof(uint16_t) + (x))

#ifdef __cplusplus
}
#endif

#endif /* DATA_TRANSFERS_H_ */