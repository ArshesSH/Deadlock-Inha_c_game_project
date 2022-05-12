#pragma once

#include "Vec2.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

typedef enum fontType
{
	FontSmall,
	FontMiddle,
	FontLarge
}FontType;

typedef struct font
{
	Vec2 pos;
	int fontWidth;
	int fontHeight;
	Color chroma;
	Surface fontTable;
	char firstChar;
	char lastChar;
	Rect textRect;

	// Must Free font List when finish use it
	Rect* fontList;
}Font;

void MakeFont( Font* f, FontType fontType );

void DrawFontText( const char* text, Vec2 pos, Color color, Font* f );

void DrawFontTextClip( const char* text, Vec2 pos, Color color, Rect clip, Font* f );

void DestroyFont( Font* f );
