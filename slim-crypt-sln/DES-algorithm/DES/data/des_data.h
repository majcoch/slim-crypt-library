/*
 * des_data.h
 *
 * Created: 26.05.2021 12:17:13
 *  Author: Micha³ Granda
 */ 


#ifndef DES_DATA_H_
#define DES_DATA_H_

#include <stdint.h>

extern const uint8_t pc_1[56];

extern const uint8_t pc_2[48];

extern const uint8_t key_shift[16];

extern const uint8_t ip[64];

extern const uint8_t expand_table[48];

extern const uint8_t s_box[8][4][16];

extern const uint8_t p[32];

extern const uint8_t inv_ip[64];

#endif /* DES_DATA_H_ */