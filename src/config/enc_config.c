/*
 * enc_config.c
 *
 * Created: 05.06.2021 11:23:49
 *  Author: Micha³ Granda
 */ 
#include "enc_config.h"

aes_128_context_t aes = { { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, { 0 } };

des_context_t des = { 0xAABB09182736CCDD, { 0 } };

tea_context_t tea = { {0x12, 0x65, 0x22, 0x55} };

uint32_t blowfish[] = { 0x01, 0x02 };