#pragma once

#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

int screenWidth;
int screenHeight;
int screenHalfWidth;
int screenHalfHeight;

void HideCursor();

void SetConsoleFontSize( int size );

void MoveCursor( int x, int y );

void SetConsoleWindowSize( int consoleWidth, int consoleHeight );

Rect GetScreenRect();

void PutPixel( int x, int y, Color c );

void DrawSpriteNonChroma( int x, int y, const Surface* const s );

void DrawSpriteRectNonChroma( int x, int y, const Rect* const srcRect, Surface* const s );

void DrawSpriteClipNonChroma( int x, int y, Rect srcRect, const Rect clip, Surface* const s );

void DrawSpriteChroma( int x, int y, const Surface* const s, Color chroma );

void DrawSpriteRectChroma( int x, int y, const Rect* const srcRect, Surface* const s, Color chroma );

void DrawSpriteClipChroma( int x, int y, Rect srcRect, Rect clip, Surface* const s, Color chroma );

void DrawSpriteSubstitute( int x, int y, const Surface* const s, Color chroma, Color subColor );

void DrawSpriteRectSubstitute( int x, int y, const Rect* const srcRect, Surface* const s, Color chroma, Color subColor );

void DrawSpriteClipSubstitute( int x, int y, Rect srcRect, const Rect clip, Surface* const s, Color chroma, Color subColor );

void DrawRect( int x0, int y0, int x1, int y1, Color c );

void DeletePixel( int x, int y );

void DeleteSurfaceScreen( Surface* pSurf, int pos_x, int pos_y );

void DeleteSizeRect( Rect rect, int pos_x, int pos_y );

void DeleteRect( Rect rect );
