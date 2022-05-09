#include "Vec2.h"

Vec2 MakeVec2( int x, int y )
{
	const Vec2 tmp = { x, y };
	return tmp;
}

void AddEqualVec2( Vec2* const lhs, Vec2 rhs )
{
	lhs->x += rhs.x;
	lhs->y += rhs.y;
}

Vec2 AddVec2( Vec2 lhs, Vec2 rhs )
{
	AddEqualVec2( &lhs, rhs );
	return lhs;
}