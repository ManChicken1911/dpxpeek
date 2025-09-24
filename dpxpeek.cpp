// dpxpeek by Bob Maple (bobm-git  [at]  burner [dot] com)
//
// Licensed under the Creative Commons Attribution-ShareAlike (CC BY-SA)
// https://creativecommons.org/licenses/by-sa/4.0/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dpxpeek.h"
#include "endian.h"
#include "helpers.h"

// Global laziness
int dpx_endian;


int main( int argc, char **argv ) {

	FILE					*inFP;
	const unsigned char		*ptr;
	char					magic[4];

	GENERICFILEHEADER				dpx;
	GENERICIMAGEHEADER				imghead;
	GENERICORIENTATIONHEADER		orienthead;
	INDUSTRYFILMINFOHEADER			filmhead;
	INDUSTRYTELEVISIONINFOHEADER	tvhead;

	printf( "dpxpeek 2025.09 by Bob Maple (bobm [at] burner [dot] com)\n" );

	if( argc < 2 ) {
		printf( "Usage: %s [FILE]\n", argv[0] );
		return(5);
	}

	inFP = fopen( argv[1], "r" );

	if( !inFP ) {
		printf( "Unable to open %s\n", argv[1] );
		return(5);
	}

	// Look to see if this is a DPX file first

	if( fread( &magic, sizeof( magic ), 1, inFP ) ) {

		if( magic[0] == 'S' && magic[1] == 'D' && magic[2] == 'P' && magic[3] == 'X' )	// Big-endian (Motorola)
			dpx_endian = 1;
		else if( magic[0] == 'X' && magic[1] == 'P' && magic[2] == 'D' && magic[3] == 'S' ) // Little-endian (Intel)
			dpx_endian = 0;
		else {
			printf( "File is not a DPX file\n" );
			fclose( inFP );
			return(5);
		}
	}
	else {
		printf( "File is not a DPX file\n" );
		fclose( inFP );
		return(5);
	}

	// Rewind
	fseek( inFP, 0, SEEK_SET );

	printf( "\n" );
	printf( "Reading DPX header of %lu bytes\n", sizeof( GENERICFILEHEADER ) );
	fread( &dpx, sizeof( GENERICFILEHEADER ), 1, inFP );

	printf( "Reading Image header of %lu bytes\n", sizeof( GENERICIMAGEHEADER ) );
	fread( &imghead, sizeof( GENERICIMAGEHEADER ), 1, inFP );

	printf( "Reading Orientation header of %lu bytes\n", sizeof( GENERICORIENTATIONHEADER ) );
	fread( &orienthead, sizeof( GENERICORIENTATIONHEADER ), 1, inFP );

	printf( "Reading Film header of %lu bytes\n", sizeof( INDUSTRYFILMINFOHEADER ) );
	fread( &filmhead, sizeof( INDUSTRYFILMINFOHEADER ), 1, inFP );

	printf( "Reading Video header of %lu bytes\n", sizeof( INDUSTRYTELEVISIONINFOHEADER ) );
	fread( &tvhead, sizeof( INDUSTRYTELEVISIONINFOHEADER ), 1, inFP );

	fclose( inFP );

	printf( "\n-- Generic Headers --\n\n" );

	EndianSwap32( (unsigned char *)&dpx.UserSize );

	ptr = (unsigned char *)&dpx.Magic;
	print_prebuf( "Magic Number" );
	printf( "%c%c%c%c ", *ptr, *(ptr+1), *(ptr+2), *(ptr+3) );

	if( dpx_endian )
		printf( "(big endian)\n" );
	else
		printf( "(little endian)\n" );

	print_DPXstring( "Version",			dpx.Version );
	print_DPXstring( "Filename",		dpx.FileName );
	print_DPXstring( "Timestamp",		dpx.TimeDate );
	print_DPXstring( "Creator",			dpx.Creator );
	print_DPXstring( "Project",			dpx.Project );
	print_DPXstring( "Copyright",		dpx.Copyright );
	print_DPXstring( "User Data Chunk", dpx.UserSize ? (char *)"Yes" : (char *)"No" );
	print_DPXint32 ( "User Data Size",  dpx.UserSize );

	printf( "\n-- Image Headers --\n\n" );

	EndianSwap16( (unsigned char *)&imghead.Orientation );
	EndianSwap16( (unsigned char *)&imghead.NumberElements );
	EndianSwap32( (unsigned char *)&imghead.PixelsPerLine );
	EndianSwap32( (unsigned char *)&imghead.LinesPerElement );

	print_prebuf( "Orientation" );
	switch( imghead.Orientation ) {
		case 0:	printf( "LtoR, TtoB\n" ); break;
		case 1: printf( "RtoL, TtoB\n" ); break;
		case 2: printf( "LtoR, BtoT\n" ); break;
		case 3: printf( "RtoL, BtoT\n" ); break;
		case 4: printf( "TtoB, LtoR\n" ); break;
		case 5: printf( "TtoB, RtoL\n" ); break;
		case 6: printf( "BtoT, LtoR\n" ); break;
		case 7: printf( "BtoT, RtoL\n" ); break;
	}

	print_DPXint32( "Width",		imghead.PixelsPerLine );
	print_DPXint32( "Height",		imghead.LinesPerElement );
	print_DPXint16( "Num Elements",	imghead.NumberElements );

	for( int i = 0; i < imghead.NumberElements; i++ ) {

		printf( "\n [Image Element %u of %u]\n\n", i+1, imghead.NumberElements );

		print_DPXstring( "Description", imghead.ImageElement[i].Description );

		EndianSwap32( (unsigned char *)&imghead.ImageElement[i].DataSign );
		EndianSwap32( (unsigned char *)&imghead.ImageElement[i].LowData );
		EndianSwap32( (unsigned char *)&imghead.ImageElement[i].LowQuantity );
		EndianSwap32( (unsigned char *)&imghead.ImageElement[i].HighData );
		EndianSwap32( (unsigned char *)&imghead.ImageElement[i].HighQuantity );
		EndianSwap16( (unsigned char *)&imghead.ImageElement[i].Packing );
		EndianSwap16( (unsigned char *)&imghead.ImageElement[i].Encoding );
		EndianSwap16( (unsigned char *)&imghead.ImageElement[i].EndOfLinePadding );
		EndianSwap16( (unsigned char *)&imghead.ImageElement[i].EndOfImagePadding );

		print_DPXstring( "Data Sign", imghead.ImageElement[i].DataSign ? (char *)"Signed" : (char *)"Unsigned" );

		print_DPXint32( "Low Data", 		imghead.ImageElement[i].LowData );
		print_DPXfloat( "Low Quantity",		imghead.ImageElement[i].LowQuantity );

		print_DPXint32( "High Data", 		imghead.ImageElement[i].HighData );
		print_DPXfloat( "High Quantity",	imghead.ImageElement[i].HighQuantity );

		print_prebuf( "Descriptor" );
		switch( imghead.ImageElement[i].Descriptor ) {
			case 0:   printf( "User-defined\n" ); break;
			case 1:   printf( "Red\n" ); break;
			case 2:   printf( "Green\n" ); break;
			case 3:   printf( "Blue\n" ); break;
			case 4:   printf( "Alpha\n" ); break;
			case 6:   printf( "Luma\n" ); break;
			case 7:   printf( "Chroma\n" ); break;
			case 8:   printf( "Depth\n" ); break;
			case 9:   printf( "Composite video\n" ); break;
			case 50:  printf( "RGB\n" ); break;
			case 51:  printf( "RGBA\n" ); break;
			case 52:  printf( "ABGR\n" ); break;
			case 100: printf( "CbYCrY\n" ); break;
			case 101: printf( "CbYaCrYa\n" ); break;
			case 102: printf( "CbYCr\n" ); break;
			case 103: printf( "CbYCra\n" ); break;
			case 150:
			case 151:
			case 152:
			case 153:
			case 154:
			case 155:
			case 156: printf( "User-defined\n" ); break;
		}

		print_prebuf( "Transfer" );
		if( imghead.ImageElement[i].Transfer >= 13 )
			printf( "Invalid (Reserved)\n" );
		else {
			switch( imghead.ImageElement[i].Transfer ) {
				case 0:  printf( "User-defined\n" ); break;
				case 1:  printf( "Print density\n" ); break;
				case 2:  printf( "Linear\n" ); break;
				case 3:  printf( "Log\n" ); break;
				case 4:  printf( "Unspecified video\n" ); break;
				case 5:  printf( "SMPTE 240M\n" ); break;
				case 6:  printf( "CCIR 709\n" ); break;
				case 7:  printf( "CCIR 601 B/G\n" ); break;
				case 8:  printf( "CCIR 601 M\n" ); break;
				case 9:  printf( "NTSC composite (SMPTE 170M)\n" ); break;
				case 10: printf( "PAL composite (CCIR 624-4)\n" ); break;
				case 11: printf( "Linear Z-Depth\n" ); break;
				default: printf( "Z-Depth User Defined\n" ); break;
			}
		}

		print_prebuf( "Colorimetric" );
		if( imghead.ImageElement[i].Colorimetric >= 13 )
			printf( "Invalid (Reserved)\n" );
		else {
			switch( imghead.ImageElement[i].Colorimetric ) {
				case 0:  printf( "User-defined\n" ); break;
				case 1:  printf( "Print density\n" ); break;
				case 4:  printf( "Unspecified video\n" ); break;
				case 5:  printf( "SMPTE 240M\n" ); break;
				case 6:  printf( "CCIR 709\n" ); break;
				case 7:  printf( "CCIR 601 B/G\n" ); break;
				case 8:  printf( "CCIR 601 M\n" ); break;
				case 9:  printf( "NTSC composite\n" ); break;
				case 10: printf( "PAL composite\n" ); break;
				default: printf( "N/A\n" ); break;
			}
		}

		print_DPXint8  ( "Bit Depth",	imghead.ImageElement[i].BitSize );
		print_DPXstring( "Packing", 	imghead.ImageElement[i].Packing ? (char *)"Filled 32-bit" : (char *)"Packed 32-bit" );
		print_DPXstring( "RLE Encoding",imghead.ImageElement[i].Encoding ? (char *)"Yes" : (char *)"None" );
		print_DPXint32 ( "EOL Padding",	imghead.ImageElement[i].EndOfLinePadding, true, " bytes" );
		print_DPXint32 ( "Img Padding",	imghead.ImageElement[i].EndOfImagePadding, true, " bytes" );
	}

	printf( "\n-- Orientation Headers --\n\n" );

	EndianSwap32( (unsigned char *)&orienthead.XOffset );
	EndianSwap32( (unsigned char *)&orienthead.YOffset );
	EndianSwap32( (unsigned char *)&orienthead.XOriginalSize );
	EndianSwap32( (unsigned char *)&orienthead.YOriginalSize );
	EndianSwap32( (unsigned char *)&orienthead.AspectRatio[0] );
	EndianSwap32( (unsigned char *)&orienthead.AspectRatio[1] );
	EndianSwap16( (unsigned char *)&orienthead.Border[0] );
	EndianSwap16( (unsigned char *)&orienthead.Border[1] );
	EndianSwap16( (unsigned char *)&orienthead.Border[2] );
	EndianSwap16( (unsigned char *)&orienthead.Border[3] );

	print_DPXint32( "Offset X",		orienthead.XOffset );
	print_DPXint32( "Offset Y",		orienthead.YOffset );
	print_DPXint32( "Orig Size X",	orienthead.XOriginalSize );
	print_DPXint32( "Orig Size Y",	orienthead.YOriginalSize );

	print_DPXstring( "Source File",		orienthead.FileName );
	print_DPXstring( "Timestamp",		orienthead.TimeDate );
	print_DPXstring( "Input Device",	orienthead.InputName );
	print_DPXstring( "Device Ser#",		orienthead.InputSN );

	if( orienthead.Border[0] == 0xFFFF )
		print_DPXstring( "Border", (char *)UNDEF_STR );
	else {
		print_DPXint16( "Border X Left",	orienthead.Border[0] );
		print_DPXint16( "Border X Right",	orienthead.Border[1] );
		print_DPXint16( "Border Y Top",		orienthead.Border[2] );
		print_DPXint16( "Border Y Bottom",	orienthead.Border[3] );
	}

	if( orienthead.AspectRatio[0] == 0xFFFFFFFF )
		print_DPXstring( "Pixel Aspect", (char *)UNDEF_STR );
	else {
		print_DPXint32( "Pixel Aspect", orienthead.AspectRatio[0], false, ":" );
		print_DPXint32( "", orienthead.AspectRatio[1], false, " (" );
		print_DPXfloat( "", (orienthead.AspectRatio[0] / orienthead.AspectRatio[1]), true, ")" );
	}

	printf( "\n-- Film Industry Header --\n\n" );

	EndianSwap32( (unsigned char *)&filmhead.FramePosition );
	EndianSwap32( (unsigned char *)&filmhead.SequenceLen );
	EndianSwap32( (unsigned char *)&filmhead.HeldCount );

	print_DPXstring( "Film ID Code",	filmhead.FilmMfgId );
	print_DPXstring( "Film Type",		filmhead.FilmType );
	print_DPXstring( "Perf Offset",		filmhead.Offset );
	print_DPXstring( "Prefix",			filmhead.Prefix );
	print_DPXstring( "Count",			filmhead.Count );
	print_DPXstring( "Film Format", 	filmhead.Format );

	print_DPXint32( "Frame Pos",		filmhead.FramePosition );
	print_DPXint32( "Sequence Len", 	filmhead.SequenceLen );
	print_DPXint32( "Frame Held", 		filmhead.HeldCount );

	EndianSwap32( (unsigned char *)&filmhead.FrameRate );
	EndianSwap32( (unsigned char *)&filmhead.ShutterAngle );

	print_DPXfloat( "FPS",				filmhead.FrameRate );
	print_DPXfloat( "Shutter Angle",	filmhead.ShutterAngle );

	print_DPXstring( "Frame ID", 		filmhead.FrameId );
	print_DPXstring( "Slate Info",		filmhead.SlateInfo );


	printf( "\n-- Television Industry Header\n\n" );

	EndianSwap32( (unsigned char *)&tvhead.FrameRate );
	EndianSwap32( (unsigned char *)&tvhead.TimeCode );
	EndianSwap32( (unsigned char *)&tvhead.Gamma );
	EndianSwap32( (unsigned char *)&tvhead.BlackLevel );
	EndianSwap32( (unsigned char *)&tvhead.BlackGain );

	if( tvhead.TimeCode == 0xFFFFFFFF )
		print_DPXstring( "Timecode", (char *)UNDEF_STR );
	else {
		print_prebuf( "Timecode" );
		printf( "%u%u:%u%u:%u%u:%u%u\n", (unsigned int)(tvhead.TimeCode & 0xF0000000) >> 28, (tvhead.TimeCode & 0xF000000) >> 24,
							(tvhead.TimeCode & 0xF00000) >> 20, (tvhead.TimeCode & 0xF0000) >> 16,
							(tvhead.TimeCode & 0xF000) >> 12, (tvhead.TimeCode & 0xF00) >> 8,
							(tvhead.TimeCode & 0xF0) >> 4, (tvhead.TimeCode & 0xF) );
	}

	print_DPXfloat( "FPS",			tvhead.FrameRate );
	print_DPXint8 ( "Interlace",	tvhead.Interlace );
	print_DPXfloat( "Gamma",		tvhead.Gamma );
	print_DPXfloat( "Black Level",	tvhead.BlackLevel );
	print_DPXfloat( "Black Gain",	tvhead.BlackGain );

	printf( "\n" );
}
