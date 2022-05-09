#pragma once

#include "Colors.h"

void HideCursor();

void SetConsoleFontSize( int size );

void MoveCursor( int x, int y );

void SetConsoleWindowSize( int consoleWidth, int consoleHeight );

void PutPixel( int x, int y, Color c );

void DrawRect( int x0, int y0, int x1, int y1, Color c );

void DeletePixelInt( int x, int y );