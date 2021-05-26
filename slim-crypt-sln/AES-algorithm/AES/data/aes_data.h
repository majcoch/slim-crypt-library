/*
 * aes_data.h
 *
 * Created: 26.05.2021 11:14:30
 *  Author: Micha³ Granda
 */ 


#ifndef AES_DATA_H_
#define AES_DATA_H_

#include <stdint.h>

extern const uint8_t aes_s_box[256];

extern const uint8_t aes_inv_s_box[256];

extern const uint8_t aes_rcon[11];

#endif /* AES_DATA_H_ */
