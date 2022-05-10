#pragma once

typedef struct vec2
{
	int x;
	int y;
} Vec2;

Vec2 MakeVec2( int x, int y );

void Vec2AddEqual( Vec2* lhs, Vec2 rhs );

Vec2 Vec2Add( Vec2 lhs, Vec2 rhs );

void Vec2SubEqual( Vec2* lhs, Vec2 rhs );

Vec2 Vec2Sub( Vec2 lhs, Vec2 rhs );

void Vec2MulEqual( Vec2* lhs, int rhs );

Vec2 Vec2Mul( Vec2 lhs, int rhs );

void Vec2DivEqual( Vec2* lhs, int rhs );

Vec2 Vec2Div( Vec2 lhs, int rhs );

int GetVec2LengthSq( Vec2 src );

int GetVec2Length( Vec2 src );

Vec2 GetVec2Normalized( Vec2 src );

void NormalizeVec2( Vec2* src );
