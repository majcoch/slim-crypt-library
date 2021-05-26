/*
 * blowfish_data.h
 *
 * Created: 26.05.2021 15:48:05
 *  Author: Micha³ Granda
 */ 


#ifndef BLOWFISH_DATA_H_
#define BLOWFISH_DATA_H_

#include <stdint.h>
#include <avr/pgmspace.h>

extern const uint32_t p_box[18];

extern const uint32_t s_box[4][256];

#endif /* BLOWFISH_DATA_H_ */