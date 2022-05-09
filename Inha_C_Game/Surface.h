
#pragma once

#include "Colors.h"
#include "Rect.h"

#define PIXEL_ALIGN 4
#define PIXEL_SIZE 3

typedef struct surface
{
	int width;
	int height;
	Color* pPixels;
}Surface;

void MakeSurface( const char* filename, Surface* pSurface );

Color SurfacePutPixel( int x, int y, Color c, Surface* pSurface );

Color SurfaceGetPixel( const Surface* const pSurface, int x, int y );

int SurfaceGetWidth( const Surface* const pSurface );

int SurfaceGetHeight( const Surface* const pSurface );

Rect SurfaceGetRect( const Surface* const pSurface );
