#pragma once

#include "Surface.h"

typedef struct tile
{
	Vec2 pos;
	Surface* sprite;
	Rect rect;
	int width;
	int height;
	Color chroma;
}Tile;

typedef struct ground
{
	// Must free tiles
	Vec2 pos;
	Tile* tiles;
	int tileCount;
	Surface* sprite;
	Rect rect;
}Ground;

void MakeFlatGround( Ground* ground, Surface* sprite, Vec2 startPos, int count, Color chroma );

void MakeTile( Tile* tile, Surface* surf, Vec2 pos, Color chroma );

void DestroyGround( Ground* ground );

void DrawGround( Ground* ground );
