#pragma once

#include "Colors.h"

void HideCursor();

void SetConsoleFontSize( int size );

void MoveCursor( int x, int y );

void SetConsoleWindowSize( int consoleWidth, int consoleHeight );

void PutPixel( int x, int y, Color c );

void DeletePixelInt( int x, int y );