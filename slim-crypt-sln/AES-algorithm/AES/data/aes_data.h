/*
 * aes_data.h
 *
 * Created: 26.05.2021 11:14:30
 *  Author: Micha³ Granda
 */ 


#ifndef AES_DATA_H_
#define AES_DATA_H_

#include <stdint.h>

extern const uint8_t s_box[256];

extern const uint8_t inv_s_box[256];

extern const uint8_t rcon[11];

#endif /* AES_DATA_H_ */
