#include "Vec2.h"

Vec2 MakeVec2( int x, int y )
{
	const Vec2 tmp = { x, y };
	return tmp;
}

void Vec2AddEqual( Vec2* const lhs, Vec2 rhs )
{
	lhs->x += rhs.x;
	lhs->y += rhs.y;
}

Vec2 Vec2Add( Vec2 lhs, Vec2 rhs )
{
	Vec2AddEqual( &lhs, rhs );
	return lhs;
}

void Vec2SubEqual( Vec2* const lhs, Vec2 rhs )
{
	lhs->x -= rhs.x;
	lhs->y -= rhs.y;
}

Vec2 Vec2Sub( Vec2 lhs, Vec2 rhs )
{
	Vec2SubEqual( &lhs, rhs );
	return lhs;
}

void Vec2MulEqual( Vec2* const lhs, int rhs )
{
	lhs->x *= rhs;
	lhs->y *= rhs;
}

Vec2 Vec2Mul( Vec2 lhs, int rhs )
{
	Vec2MulEqual( &lhs, rhs );
	return lhs;
}