#include "Rect.h"

Rect MakeRect( int left, int right, int top, int bottom )
{
	const Rect rt = { left, right, top, bottom };
	return rt;
}

Rect MakeRectByConner( Vec2 topLeft, Vec2 bottomRight )
{
	const Rect rt = { (int)topLeft.x, (int)bottomRight.x, (int)topLeft.y, (int)bottomRight.y };
	return rt;
}

Rect MakeRectBySize( Vec2 topLeft, int width, int height )
{
	const Rect rt = MakeRectByConner( topLeft, Vec2Add( topLeft, MakeVec2( (float)width, (float)height ) ) );
	return rt;
}


bool RectIsOverlappingWith( Rect target, Rect other )
{
	return target.right > other.left && target.left < other.right
		&& target.bottom > other.top && target.top < other.bottom;
}

bool RectIsContainedBy( Rect target, Rect other )
{
	return target.left >= other.left && target.right <= other.right
		&& target.top >= other.top && target.bottom <= other.bottom;
}

bool RectContains( Rect target, Vec2 point )
{
	return point.x >= target.left && point.x < target.right && point.y >= target.top && point.y < target.bottom;
}

Rect RectFromCenter( Vec2 center, int halfWidth, int halfHeight )
{
	const Vec2 half = MakeVec2( (float)halfWidth, (float)halfHeight );
	return MakeRectByConner( Vec2Sub( center , half ) , Vec2Add(center, half) );
}

Rect RectGetExpanded( Rect target, int offset )
{
	return MakeRect( target.left - offset, target.right + offset, target.top - offset, target.bottom + offset );
}

Vec2 RectGetCenter(Rect target)
{
	return MakeVec2( (target.left + target.right) / 2.0f, (target.top + target.bottom) / 2.0f );
}

int RectGetWidth( Rect target )
{
	return target.right - target.left;
}

int RectGetHeight( Rect target )
{
	return target.bottom - target.top;
}