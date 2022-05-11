#include "Colors.h"

Color MakeRGB( unsigned char r, unsigned char g, unsigned char b )
{
	Color tmp;
	tmp.dword = (r << 16) | (g << 8) | b;
	return tmp;
}
const unsigned char GetX( Color color )
{
	return (color.dword >> 24u) & 0xFFu;
}
const unsigned char GetA( Color color )
{
	return GetX( color );
}
const unsigned char GetR( Color color )
{
	return (color.dword >> 16u) & 0xFFu;
}
const unsigned char GetG( Color color )
{
	return (color.dword >> 8u) & 0xFFu;
}
const unsigned char GetB( Color color )
{
	return (color.dword) & 0xFFu;
}
void SetX( Color* color, unsigned char x )
{
	color->dword = (color->dword & 0xFF00FFFFu) | (x << 24u);
}
void SetA( Color* color, unsigned char a )
{
	SetX( color, a );
}
void SetR( Color* color, unsigned char r )
{
	color->dword = (color->dword & 0xFF00FFFFu) | (r << 16u);
}
void SetG( Color* color, unsigned char g )
{
	color->dword = (color->dword & 0xFF00FFFFu) | (g << 8u);
}
void SetB( Color* color, unsigned char b )
{
	color->dword = (color->dword & 0xFF00FFFFu) | b;
}