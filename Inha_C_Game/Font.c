#include "Font.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Graphics.h"

void MakeFont( Font* f, FontType fontType )
{
	const int sectionCount = 32;
	const int sectionLine = 3;
	switch (fontType)
	{
	case FontSmall:
		MakeSurface( "src/images/Fixedsys8x14.bmp", &(f->fontTable) );
		f->pos.x = 0;
		f->pos.y = 0;
		f->fontWidth = 8;
		f->fontHeight = 14;
		f->firstChar = ' ';
		f->lastChar = '~';
		f->chroma = WHITE;
		break;
	case FontMedium:
		MakeSurface( "src/images/Fixedsys16x28.bmp", &(f->fontTable) );
		f->pos.x = 0;
		f->pos.y = 0;
		f->fontWidth = 16;
		f->fontHeight = 28;
		f->firstChar = ' ';
		f->lastChar = '~';
		f->chroma = WHITE;
		break;
	case FontLarge:
		MakeSurface( "src/images/Fixedsys32x56.bmp", &(f->fontTable) );
		f->pos.x = 0;
		f->pos.y = 0;
		f->fontWidth = 32;
		f->fontHeight = 56;
		f->firstChar = ' ';
		f->lastChar = '~';
		f->chroma = WHITE;
		break;
	}

	// Reserve fontList (malloc)
	f->fontList = (Rect*)malloc( sizeof( Rect ) * sectionCount * sectionLine );
	if (f->fontList == NULL)
	{
		exit( 0 );
	}
	
	for (int iLine = 0; iLine < sectionLine; iLine++)
	{
		for (int iSection = 0; iSection < sectionCount; iSection++)
		{
			const Rect tmp = MakeRect(
				f->pos.x + iSection * f->fontWidth,
				f->pos.x + (iSection + 1) * f->fontWidth,
				f->pos.y + iLine * f->fontHeight,
				f->pos.y + (iLine + 1) * f->fontHeight );
			f->fontList[iLine * sectionCount + iSection] = tmp;
		}
	}
}

void DrawFontText( const char* text, Vec2 pos, Color color, Font* f )
{
	DrawFontTextClip( text, pos, color, GetScreenRect(), f );
}

void DrawFontTextClip( const char* text, Vec2 pos, Color color, Rect clip, Font* f )
{
	int iWidth = 0;
	int iHeight = 0;
	int maxWidth = 0;

	for (size_t i = 0; i < strlen( text ); i++)
	{
		const char c = text[i];
		assert( c >= f->firstChar && c <= f->lastChar || c == '\n' );
		if (c == '\n')
		{
			iHeight++;
			iWidth = 0;
		}
		else
		{
			DrawSpriteClipSubstitute( pos.x + (iWidth * (f->fontWidth)), pos.y + (iHeight * (f->fontHeight) ), f->fontList[c - ' '], clip, &f->fontTable, f->chroma, color );
			iWidth++;
		}
		maxWidth = max( maxWidth, iWidth );
	}

	const int rectRight = (maxWidth * (f->fontWidth));
	const int rectBottom = ((iHeight + 1) * (f->fontHeight));
	f->textRect = MakeRectBySize( pos, rectRight, rectBottom );
}


void DestroyFont( Font* f )
{
	free( f->fontList );
	f->fontList = NULL;
}