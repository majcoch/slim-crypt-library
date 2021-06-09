/*
 * evaluation.h
 *
 * Created: 05.06.2021 11:13:00
 *  Author: Micha³ Granda
 */ 


#ifndef EVALUATION_H_
#define EVALUATION_H_

#include <stdint.h>

uint32_t aes_enc_eval(uint8_t* data, uint16_t* size);
uint32_t aes_dec_eval(uint8_t* data, uint16_t* size);

uint32_t des_enc_eval(uint8_t* data, uint16_t* size);
uint32_t des_dec_eval(uint8_t* data, uint16_t* size);

uint32_t tea_enc_eval(uint8_t* data, uint16_t* size);
uint32_t tea_dec_eval(uint8_t* data, uint16_t* size);

uint32_t blowfish_enc_eval(uint8_t* data, uint16_t* size);
uint32_t blowfish_dec_eval(uint8_t* data, uint16_t* size);

uint32_t sha1_hash_eval(uint8_t* data, uint16_t* size);

#endif /* EVALUATION_H_ */