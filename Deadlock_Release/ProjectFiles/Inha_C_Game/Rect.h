#pragma once
#include <stdbool.h>
#include "Vec2.h"

typedef struct rect
{
	int left;
	int right;
	int top;
	int bottom;
}Rect;

Rect MakeRect( int left, int right, int top, int bottom );

Rect MakeRectByConner( Vec2 topLeft, Vec2 bottomRight );

Rect MakeRectBySize( Vec2 topLeft, int width, int height );

bool RectIsOverlappingWith( Rect target, Rect other );	

bool RectIsContainedBy( Rect target, Rect other );

bool RectContains( Rect target, Vec2 point );

Rect RectFromCenter( Vec2 center, int halfWidth, int halfHeight );

Rect RectGetExpanded( Rect target, int offset );

Vec2 RectGetCenter( Rect target );

int RectGetWidth( Rect target );

int RectGetHeight( Rect target );
