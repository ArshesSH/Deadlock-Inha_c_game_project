#include "Font.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Graphics.h"

void MakeFont( Font* f, int x, int y, int width, int height, int sectionCount, int sectionLine, Color c, char firstChar, char lastChar )
{
	MakeSurface( "src/images/Fixedsys16x28.bmp", &(f->fontTable) );
	f->chroma = c;
	f->fontWidth = width;
	f->fontHeight = height;
	f->firstChar = firstChar;
	f->lastChar = lastChar;
	f->pos.x = x;
	f->pos.y = y;
	
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
				x + iSection * width,
				x + (iSection + 1) * width,
				y + iLine * height,
				y + (iLine + 1) * height );
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
	}
}


void DestroyFont( Font* f )
{
	free( f->fontList );
	f->fontList = NULL;
}