#pragma once

typedef struct vec2
{
	int x;
	int y;
} Vec2;

Vec2 MakeVec2( int x, int y );

void Vec2AddEqual( Vec2* const lhs, Vec2 rhs );

Vec2 Vec2Add( Vec2 lhs, Vec2 rhs );

void Vec2SubEqual( Vec2* const lhs, Vec2 rhs );

Vec2 Vec2Sub( Vec2 lhs, Vec2 rhs );

void Vec2MulEqual( Vec2* const lhs, int rhs );

Vec2 Vec2Mul( Vec2 lhs, int rhs );