#include "Vec2.h"
#include "MathSH.h"
#include <math.h>

Vec2 MakeVec2( float x, float y )
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

void Vec2MulEqual( Vec2* lhs, float rhs )
{
	lhs->x *= rhs;
	lhs->y *= rhs;
}

Vec2 Vec2Mul( Vec2 lhs, float rhs )
{
	Vec2MulEqual( &lhs, rhs );
	return lhs;
}

void Vec2DivEqual( Vec2* lhs, float rhs )
{
	lhs->x /= rhs;
	lhs->y /= rhs;
}

Vec2 Vec2Div( Vec2 lhs, float rhs )
{
	Vec2DivEqual( &lhs, rhs );
	return lhs;
}


float GetVec2DotProduct( Vec2 lhs, Vec2 rhs )
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float GetVec2LengthSq( Vec2 src )
{
	return src.x * src.x + src.y * src.y;
}

float GetVec2Length( Vec2 src )
{
	return sqrtf( GetVec2LengthSq( src ) );
}

Vec2 GetVec2Normalized( Vec2 src )
{
	const float len = GetVec2Length( src );
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

float GetRadianBetween( Vec2 lhs, Vec2 rhs )
{
	return (float)(acos( GetVec2DotProduct( GetVec2Normalized( lhs ), GetVec2Normalized( rhs ) ) ));
}

float GetAngleBetween( Vec2 lhs, Vec2 rhs )
{
	return (float)(GetRadianBetween( lhs, rhs ) * (180 / PI));
}