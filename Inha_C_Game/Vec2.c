#include "Vec2.h"
#include <math.h>

Vec2 MakeVec2( int x, int y )
{
	const Vec2 tmp = { x, y };
	return tmp;
}

void Vec2AddEqual( Vec2* lhs, Vec2 rhs )
{
	lhs->x += rhs.x;
	lhs->y += rhs.y;
}

Vec2 Vec2Add( Vec2 lhs, Vec2 rhs )
{
	Vec2AddEqual( &lhs, rhs );
	return lhs;
}

void Vec2SubEqual( Vec2* lhs, Vec2 rhs )
{
	lhs->x -= rhs.x;
	lhs->y -= rhs.y;
}

Vec2 Vec2Sub( Vec2 lhs, Vec2 rhs )
{
	Vec2SubEqual( &lhs, rhs );
	return lhs;
}

void Vec2MulEqual( Vec2* lhs, int rhs )
{
	lhs->x *= rhs;
	lhs->y *= rhs;
}

Vec2 Vec2Mul( Vec2 lhs, int rhs )
{
	Vec2MulEqual( &lhs, rhs );
	return lhs;
}

void Vec2DivEqual( Vec2* lhs, int rhs )
{
	lhs->x /= rhs;
	lhs->y /= rhs;
}

Vec2 Vec2Div( Vec2 lhs, int rhs )
{
	Vec2DivEqual( &lhs, rhs );
	return lhs;
}

int GetVec2LengthSq( Vec2 src )
{
	return src.x * src.x + src.y * src.y;
}

int GetVec2Length( Vec2 src )
{
	return (int)sqrt( GetVec2LengthSq( src ) );
}

Vec2 GetVec2Normalized( Vec2 src )
{
	const int len = GetVec2Length( src );
	if (len != 0)
	{
		return Vec2Mul( src, (1 / len) );
	}
	return src;
}

void NormalizeVec2( Vec2* src )
{
	*src = GetVec2Normalized( *src );
}