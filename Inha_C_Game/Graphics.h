#pragma once

#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

static int screenWidth;
static int screenHeight;

void HideCursor();

void SetConsoleFontSize( int size );

void MoveCursor( int x, int y );

void SetConsoleWindowSize( int consoleWidth, int consoleHeight );

Rect GetScreenRect();

void PutPixel( int x, int y, Color c );

void DrawSpriteNonChroma( int x, int y, const Surface* const s );

void DrawSpriteRectNonChroma( int x, int y, const Rect* const srcRect, const Surface* const s );

void DrawSpriteClipNonChroma( int x, int y, Rect srcRect, const Rect clip, const Surface* const s );

void DrawSpriteChroma( int x, int y, const Surface* const s, Color chroma );

void DrawSpriteRectChroma( int x, int y, const Rect* const srcRect, const Surface* const s, Color chroma );

void DrawSpriteClipChroma( int x, int y, Rect srcRect, Rect clip, const Surface* const s, Color chroma );

void DrawRect( int x0, int y0, int x1, int y1, Color c );

void DeletePixelInt( int x, int y );