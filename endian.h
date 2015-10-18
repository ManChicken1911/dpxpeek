// dpxpeek by Bob Maple (bobm [at] burner.com)
//
// Licensed under the Creative Commons Attribution-ShareAlike (CC BY-SA)
// https://creativecommons.org/licenses/by-sa/4.0/

#include <stdint.h>

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

extern void EndianSwap32( unsigned char * );
extern void EndianSwap16( unsigned char * );
