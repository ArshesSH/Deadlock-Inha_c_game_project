
#include "Surface.h"

#include <stdio.h>
#include <assert.h>
#include <Windows.h>
#include <stdbool.h>
#include "Graphics.h"

void MakeSurface ( const char* filename, Surface* pSurface )
{
	FILE* pFile;
	
	if (fopen_s( &pFile, filename, "rb" ) != 0)
	{
		fclose( pFile );
		return;
	}
	assert ( pFile != NULL  );

	// Read the bitmap file header
	BITMAPFILEHEADER bmFileHeader;
	fread( (char*)(&bmFileHeader), sizeof( bmFileHeader ), 1, pFile );

	// Verify that this is a .BMP file by checking bitmap id
	if (bmFileHeader.bfType != 0x4D42)
	{
		fclose( pFile );
		return;
	}

	// Read the bitmap info header
	BITMAPINFOHEADER bmInfoHeader;
	fread( (char*)(&bmInfoHeader), sizeof( bmInfoHeader ), 1, pFile );

	// Check 32bit Img
	assert( bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32 );
	const bool is32b = bmInfoHeader.biBitCount == 32;

	//assert( bmInfoHeader.biCompression == BI_RGB );

	pSurface->width = bmInfoHeader.biWidth;

	int yStart;
	int yEnd;
	int dy;
	if (bmInfoHeader.biHeight < 0)
	{
		pSurface->height = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = pSurface->height;
		dy = 1;
	}
	else
	{
		pSurface->height = bmInfoHeader.biHeight;
		yStart = pSurface->height - 1;
		yEnd = -1;
		dy = -1;
	}

	pSurface->pPixels = (Color*)malloc( sizeof( Color ) * pSurface->height * pSurface->width );

	//move file pointer to the beginning of bitmap data
	fseek( pFile, bmFileHeader.bfOffBits, SEEK_SET );
	const int padding = (PIXEL_ALIGN - (pSurface->width * PIXEL_SIZE) % PIXEL_ALIGN) % PIXEL_ALIGN;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < pSurface->width; x++)
		{
			SurfacePutPixel( x, y, MakeRGB( fgetc(pFile), fgetc( pFile ), fgetc( pFile ) ), pSurface );
			if (is32b)
			{
				fseek( pFile, 1, SEEK_CUR );
			}
		}
		if (!is32b)
		{
			fseek( pFile, padding, SEEK_CUR );
		}
	}

	fclose( pFile );
}

Color SurfacePutPixel( int x, int y, Color c, Surface* pSurface )
{
	assert( x >= 0 );
	assert( x < pSurface->width );
	assert( y >= 0 );
	assert( y < pSurface->height );
	return pSurface->pPixels[y * pSurface->width + x] = c;
}

Color SurfaceGetPixel( const Surface* const pSurface, int x, int y )
{
	assert( x >= 0 );
	assert( x < pSurface->width );
	assert( y >= 0 );
	assert( y < pSurface->height );
	return pSurface->pPixels[y * pSurface->width + x];
}

int SurfaceGetWidth( const Surface* const pSurface )
{
	return pSurface->width;
}

int SurfaceGetHeight( const Surface* const pSurface )
{
	return pSurface->height;
}

Rect SurfaceGetRect( const Surface* const pSurface )
{
	return MakeRectBySize( MakeVec2( 0, 0 ), pSurface->width, pSurface->height );
}

void DeleteSurface( Surface* pSurface )
{
	free( pSurface->pPixels );
	pSurface->pPixels = NULL;
}