// dpxpeek by Bob Maple (bobm [at] burner.com)
//
// Licensed under the Creative Commons Attribution-ShareAlike (CC BY-SA)
// https://creativecommons.org/licenses/by-sa/4.0/

#include "endian.h"

extern int dpx_endian;

void EndianSwap32( unsigned char *x ) {

	if( dpx_endian && !IS_BIG_ENDIAN ) {
		unsigned char tmp;
		// Swap outer 2 bytes

		tmp = *x;

		*x = *(x+3);
		*(x+3) = tmp;

		// Swap inner 2 bytes

		x += 1;
		tmp = *x;
		*x = *(x+1);
		*(x+1) = tmp;
	}
}

void EndianSwap16( unsigned char *x ) {

	if( dpx_endian && !IS_BIG_ENDIAN ) {
		unsigned char tmp;

		tmp = *x;

		*x = *(x+1);
		*(x+1) = tmp;
	}
}
