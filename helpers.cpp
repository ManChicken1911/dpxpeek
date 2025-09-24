// dpxpeek by Bob Maple (bobm-git  [at]  burner [dot] com)
//
// Licensed under the Creative Commons Attribution-ShareAlike (CC BY-SA)
// https://creativecommons.org/licenses/by-sa/4.0/

#include <math.h>
#include <stdio.h>

#define  UNDEF_STR "<undef>"
#define  UNDEF_STR_INF "<undef*>"

void print_prebuf( const char *prebuf ) {

	if( prebuf[0] != 0 )
		printf( "%-16s: ", prebuf );
}

void print_postbuf( const char *postbuf, int newline = true ) {

	if( postbuf[0] != 0 )
		printf( "%s", postbuf );

	if( newline )
		printf( "\n" );
}

//

void print_DPXfloat( const char *prebuf, float val, unsigned int newline = true, const char *postbuf = "" ) {

	print_prebuf( prebuf );

	if( val == 0xFFFFFFFF )
		printf( UNDEF_STR );
	else if( !isnormal( val ) )
		printf( UNDEF_STR_INF );
	else printf( "%f", val );

	print_postbuf( postbuf, newline );
}

void print_DPXint32( const char *prebuf, unsigned int val, unsigned int newline = true, const char *postbuf = "" ) {

	print_prebuf( prebuf );

	if( val == 0xFFFFFFFF )
		printf( UNDEF_STR );
	else
		printf( "%u", val );

	print_postbuf( postbuf, newline );
}

void print_DPXint16( const char *prebuf, unsigned short val, unsigned int newline = true, const char *postbuf = "" ) {

	print_prebuf( prebuf );

 	if( val == 0xFFFF )
		printf( UNDEF_STR );
	else
		printf( "%u", val );

	print_postbuf( postbuf, newline );
}

void print_DPXint8( const char *prebuf, unsigned char val, unsigned int newline = true, const char *postbuf = "" ) {

	print_prebuf( prebuf );

 	if( val == 0xFF )
		printf( UNDEF_STR );
	else
		printf( "%u", val );

	print_postbuf( postbuf, newline );
}

void print_DPXstring( const char *prebuf, char *buf, unsigned int newline = true, const char *postbuf = "" ) {

	print_prebuf( prebuf );

	if( buf[0] == 0x00 )
		printf( UNDEF_STR );
	else
		printf( "%s", buf );

	print_postbuf( postbuf, newline );
}
