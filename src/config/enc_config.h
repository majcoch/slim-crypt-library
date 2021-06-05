/*
 * enc_config.h
 *
 * Created: 05.06.2021 11:10:10
 *  Author: Micha³ Granda
 */ 


#ifndef ENC_CONFIG_H_
#define ENC_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "algorithms/sha1/sha1.h"
#include "algorithms/aes/aes.h"
#include "algorithms/des/des.h"
#include "algorithms/tea/tea.h"
#include "algorithms/blowfish/blowfish.h"

extern aes_128_context_t aes;

extern des_context_t des;

extern tea_context_t tea;

extern uint32_t blowfish[];

#ifdef __cplusplus
}
#endif

#endif /* ENC_CONFIG_H_ */