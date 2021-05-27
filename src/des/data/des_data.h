/*
 * des_data.h
 *
 * Created: 26.05.2021 12:17:13
 *  Author: Micha³ Granda
 */ 


#ifndef DES_DATA_H_
#define DES_DATA_H_

#include <stdint.h>

extern const uint8_t des_pc_1[56];

extern const uint8_t des_pc_2[48];

extern const uint8_t des_key_shift[16];

extern const uint8_t des_ip[64];

extern const uint8_t des_expand_table[48];

extern const uint8_t des_s_box[8][4][16];

extern const uint8_t des_p[32];

extern const uint8_t des_inv_ip[64];

#endif /* DES_DATA_H_ */