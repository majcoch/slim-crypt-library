/*
 * sha1_data.c
 *
 * Created: 26.05.2021 16:26:47
 *  Author: Micha³ Granda
 */ 
#include "sha1_data.h"

#ifdef __AVR__ 
	#include <avr/pgmspace.h>
	#define FLASH_MEM PROGMEM
#else
	#define FLASH_MEM
#endif // __AVR__ 

const uint32_t sha1_h[5] FLASH_MEM  = {
	0x67452301,
	0xEFCDAB89,
	0x98BADCFE,
	0x10325476,
	0xC3D2E1F0
};
