#pragma once

#include "Vec2.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

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


void MakeFont( Font* f, int x, int y, int width, int height, int sectionCount, int sectionLine, Color c, char firstChar, char lastChar, const char* filename );

void DrawFontText( const char* text, Vec2 pos, Color color, Font* f );

void DrawFontTextClip( const char* text, Vec2 pos, Color color, Rect clip, Font* f );

void DestroyFont( Font* f );
