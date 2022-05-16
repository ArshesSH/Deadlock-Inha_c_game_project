#include "Graphics.h"

#include <Windows.h>
#include <string.h>
#include <assert.h>
#include "cful.h"
#include "Vec2.h"
#include "MathSH.h"

void HideCursor()
{
    HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo( consoleHandle, &info );
}

void SetConsoleFontSize( int size )
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof( CONSOLE_FONT_INFOEX );
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    GetCurrentConsoleFontEx( hOut, 0, &fontex );
    fontex.dwFontSize.X = size;
    fontex.dwFontSize.Y = size;
    SetCurrentConsoleFontEx( hOut, NULL, &fontex );
}

void MoveCursor( int x, int y )
{
    COORD coord = { x , y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void SetConsoleWindowSize( int consoleWidth, int consoleHeight )
{
    const int halfWidth = consoleWidth / 2;
    const int halfHeight = consoleHeight / 2;

    screenWidth = halfWidth;
    screenHeight = halfHeight;
    screenHalfWidth = screenWidth / 2;
    screenHalfHeight = screenHeight / 2;
    screenXOffset = screenWidth / 9.6f;
    screenYOffset = screenHeight / 5.4f;

    DWORD dwWidth = GetSystemMetrics( SM_CXSCREEN );
    DWORD dwHeight = GetSystemMetrics( SM_CYSCREEN );

    char strWidth[5];
    char strHeight[5];
    char consolSizeStr[64] = { "mode con:cols=" };

    sprintf_s( strWidth, 5, "%d", consoleWidth );
    sprintf_s( strHeight, 5, "%d", halfHeight );
    strcat_s( consolSizeStr, 64, strWidth );
    strcat_s( consolSizeStr, 64, " lines=" );
    strcat_s( consolSizeStr, 64, strHeight );
    system( consolSizeStr );
}

Rect GetScreenRect()
{
    return MakeRect( 0, screenWidth, 0, screenHeight );
}

void PutPixel( int x, int y, Color c )
{
    MoveCursor( x * 2, y );
    SET_FG_COLOR( GetR( c ), GetG( c ), GetB( c ) );
    printf( "бс" );
}

void DrawSpriteNonChroma( int x, int y, Surface* const s )
{
    DrawSpriteClipNonChroma( x, y, SurfaceGetRect( s ), GetScreenRect(), s );
}

void DrawSpriteRectNonChroma( int x, int y, const Rect* const srcRect, Surface* const s )
{
    DrawSpriteClipNonChroma( x, y, *srcRect, GetScreenRect(), s );
}

void DrawSpriteClipNonChroma( int x, int y, Rect srcRect, const Rect clip, Surface* const s )
{
    assert( srcRect.left >= 0 );
    assert( srcRect.right <= s->width );
    assert( srcRect.top >= 0 );
    assert( srcRect.bottom <= s->height );

    if (x < clip.left)
    {
        srcRect.left += clip.left - x;
        x = clip.left;
    }
    if (y < clip.top)
    {
        srcRect.top += clip.top - y;
        y = clip.top;
    }
    if (x + RectGetWidth( srcRect ) > clip.right)
    {
        srcRect.right -= x + RectGetWidth( srcRect ) - clip.right;
    }
    if (y + RectGetHeight( srcRect ) > clip.bottom)
    {
        srcRect.bottom -= y + RectGetHeight( srcRect ) - clip.bottom;
    }

    for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
    {
        for (int sx = srcRect.left; sx < srcRect.right; sx++)
        {
            PutPixel( x + sx - srcRect.left, y + sy - srcRect.top, SurfaceGetPixel( s, sx, sy ) );
        }
    }
    s->wasDrew = true;
}


void DrawSpriteChroma( int x, int y, Surface* const s, Color chroma )
{
    DrawSpriteClipChroma( x, y, SurfaceGetRect(s), GetScreenRect(), s, chroma );
}

void DrawSpriteRectChroma( int x, int y, const Rect* const srcRect, Surface* const s, Color chroma )
{
    DrawSpriteClipChroma( x, y, *srcRect, GetScreenRect(), s, chroma );
}

void DrawSpriteClipChroma( int x, int y, Rect srcRect, const Rect clip, Surface* const s, Color chroma )
{
    assert( srcRect.left >= 0 );
    assert( srcRect.right <= SurfaceGetWidth(s) );
    assert( srcRect.top >= 0 );
    assert( srcRect.bottom <= SurfaceGetHeight(s) );

    if (x < clip.left)
    {
        srcRect.left += clip.left - x;
        x = clip.left;
    }
    if (y < clip.top)
    {
        srcRect.top += clip.top - y;
        y = clip.top;
    }
    if (x + RectGetWidth( srcRect ) > clip.right)
    {
        srcRect.right -= x + RectGetWidth( srcRect ) - clip.right;
    }
    if (y + RectGetHeight( srcRect ) > clip.bottom)
    {
        srcRect.bottom -= y + RectGetHeight( srcRect ) - clip.bottom;
    }

    for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
    {
        for (int sx = srcRect.left; sx < srcRect.right; sx++)
        {
            Color curPixelColor = SurfaceGetPixel( s, sx, sy );
            if (curPixelColor.dword != chroma.dword)
            {
                PutPixel( x + sx - srcRect.left, y + sy - srcRect.top, curPixelColor );
            }
        }
    }
    s->wasDrew = true;
}

void DrawSpriteSubstitute( int x, int y, Surface* const s, Color chroma, Color subColor )
{
    DrawSpriteClipSubstitute( x, y, SurfaceGetRect( s ), GetScreenRect(), s, chroma, subColor );
}


void DrawSpriteRectSubstitute( int x, int y, const Rect* const srcRect, Surface* const s, Color chroma, Color subColor )
{
    DrawSpriteClipSubstitute( x, y, *srcRect, GetScreenRect(), s, chroma, subColor );
}

void DrawSpriteClipSubstitute( int x, int y, Rect srcRect, const Rect clip, Surface* const s, Color chroma, Color subColor )
{
    assert( srcRect.left >= 0 );
    assert( srcRect.right <= SurfaceGetWidth( s ) );
    assert( srcRect.top >= 0 );
    assert( srcRect.bottom <= SurfaceGetHeight( s ) );

    if (x < clip.left)
    {
        srcRect.left += clip.left - x;
        x = clip.left;
    }
    if (y < clip.top)
    {
        srcRect.top += clip.top - y;
        y = clip.top;
    }
    if (x + RectGetWidth( srcRect ) > clip.right)
    {
        srcRect.right -= x + RectGetWidth( srcRect ) - clip.right;
    }
    if (y + RectGetHeight( srcRect ) > clip.bottom)
    {
        srcRect.bottom -= y + RectGetHeight( srcRect ) - clip.bottom;
    }

    for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
    {
        for (int sx = srcRect.left; sx < srcRect.right; sx++)
        {
            Color curPixelColor = SurfaceGetPixel( s, sx, sy );
            if (curPixelColor.dword != chroma.dword)
            {
                PutPixel( x + sx - srcRect.left, y + sy - srcRect.top, subColor );
            }
        }
    }
    s->wasDrew = true;
}

void DrawSpriteTitle( int x, int y, Surface* const s )
{
    Rect srcRect = SurfaceGetRect( s );
    const Rect clip = GetScreenRect();

    assert( srcRect.left >= 0 );
    assert( srcRect.right <= s->width );
    assert( srcRect.top >= 0 );
    assert( srcRect.bottom <= s->height );


    if (x < clip.left)
    {
        srcRect.left += clip.left - x;
        x = clip.left;
    }
    if (y < clip.top)
    {
        srcRect.top += clip.top - y;
        y = clip.top;
    }
    if (x + RectGetWidth( srcRect ) > clip.right)
    {
        srcRect.right -= x + RectGetWidth( srcRect ) - clip.right;
    }
    if (y + RectGetHeight( srcRect ) > clip.bottom)
    {
        srcRect.bottom -= y + RectGetHeight( srcRect ) - clip.bottom;
    }

    for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
    {
        for (int sx = srcRect.left; sx < srcRect.right; sx++)
        {
            if ((x + sx) % 2 == 0 && (y + sy) % 3 == 0)
            {
                PutPixel( x + sx - srcRect.left, y + sy - srcRect.top, SurfaceGetPixel( s, sx, sy ) );
            }

        }
    }
    s->wasDrew = true;
}


void DrawRect( int x0, int y0, int x1, int y1, Color c )
{
    if (x0 > x1)
    {
        swapI( &x0, &x1 );
    }
    if (y0 > y1)
    {
        swapI( &y0, &y1 );
    }

    for (int y = y0; y < y1; ++y)
    {
        for (int x = x0; x < x1; ++x)
        {
            PutPixel( x, y, c );
        }
    }
}

void DeletePixel( int x, int y )
{
    MoveCursor( x * 2, y );
    printf( "  " );
}

void DeleteSurfaceScreen( Surface* pSurf, int pos_x, int pos_y )
{
    DeleteSizeRect( SurfaceGetRect( pSurf ), pos_x, pos_y );
    pSurf->wasDrew = false;
}

void DeleteSizeRect( Rect rect, int pos_x, int pos_y )
{
    for (int y = rect.top; y < rect.bottom; ++y)
    {
        for (int x = rect.left; x < rect.right; ++x)
        {
            DeletePixel( x + pos_x, y + pos_y );
        }
    }
}

void DeleteRect( Rect rect )
{
    for ( int y = rect.top; y < rect.bottom; ++y )
    {
        for ( int x = rect.left; x < rect.right; ++x )
        {
            DeletePixel( x, y );
        }
    }
}