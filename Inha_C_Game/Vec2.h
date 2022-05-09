#pragma once

typedef struct vec2
{
	int x;
	int y;
} Vec2;

Vec2 MakeVec2( int x, int y );

void AddEqualVec2( Vec2* const lhs, Vec2 rhs );

Vec2 AddVec2( Vec2 lhs, Vec2 rhs );