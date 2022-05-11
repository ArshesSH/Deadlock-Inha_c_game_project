#pragma once

typedef struct vec2
{
	float x;
	float y;
} Vec2;

Vec2 MakeVec2( float x, float y );

void Vec2AddEqual( Vec2* lhs, Vec2 rhs );

Vec2 Vec2Add( Vec2 lhs, Vec2 rhs );

void Vec2SubEqual( Vec2* lhs, Vec2 rhs );

Vec2 Vec2Sub( Vec2 lhs, Vec2 rhs );

void Vec2MulEqual( Vec2* lhs, float rhs );

Vec2 Vec2Mul( Vec2 lhs, float rhs );

void Vec2DivEqual( Vec2* lhs, float rhs );

Vec2 Vec2Div( Vec2 lhs, float rhs );

float GetVec2DotProduct( Vec2 lhs, Vec2 rhs );

float GetVec2LengthSq( Vec2 src );

float GetVec2Length( Vec2 src );

Vec2 GetVec2Normalized( Vec2 src );

void NormalizeVec2( Vec2* src );

float GetRadianBetween( Vec2 lhs, Vec2 rhs );

float GetAngleBetween( Vec2 lhs, Vec2 rhs );

void RotateVec2( Vec2* src, float angle );

Vec2 GetRotateVec2( Vec2 src, float angle );
