#pragma once

#define WHITE		MakeRGB( 255u, 255u, 255u )
#define BLACK		MakeRGB( 0u, 0u, 0u )
#define GRAY		MakeRGB( 0x80u, 0x80u, 0x80u )
#define LIGHTGRAY	MakeRGB( 0xD3u, 0xD3u, 0xD3u )
#define RED			MakeRGB( 255u, 0u, 0u )
#define GREEN		MakeRGB( 0u, 255u, 0u )
#define BLUE		MakeRGB( 0u, 0u, 255u )
#define YELLOW		MakeRGB( 255u, 255u, 0u )
#define CYAN		MakeRGB( 0u, 255u, 255u )
#define MAGENTA		MakeRGB( 255u, 0u, 255u )



typedef struct Color
{
	unsigned int dword;
}Color;

Color MakeRGB( unsigned char r, unsigned char g, unsigned char b );

const unsigned char GetX( Color color );

const unsigned char GetA( Color color );

const unsigned char GetR( Color color );

const unsigned char GetG( Color color );

const unsigned char GetB( Color color );

void SetX( Color* color, unsigned char x );

void SetA( Color* color, unsigned char a );

void SetR( Color* color, unsigned char r );

void SetG( Color* color, unsigned char g );

void SetB( Color* color, unsigned char b );
