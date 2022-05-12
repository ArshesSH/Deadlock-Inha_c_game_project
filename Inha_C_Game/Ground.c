#include "Ground.h"

#include <stdlib.h>
#include "Graphics.h"

void MakeFlatGround( Ground* ground, Surface* sprite, Vec2 startPos, int count, Color chroma )
{
	ground->sprite = sprite;
	ground->tileCount = count;
	ground->pos = startPos;
	ground->tiles = (Tile*)malloc( sizeof( Tile ) * count );

	Vec2 pos = startPos;
	for ( int i = 0; i < count; i++ )
	{
		MakeTile( &(ground->tiles[i]), ground->sprite, pos, chroma );
		pos.x += ground->tiles[i].width;
	}
	pos.y += ground->tiles[0].height;

	ground->rect = MakeRectByConner( startPos, pos );
}

void MakeTile( Tile* tile, Surface* surf, Vec2 pos, Color chroma )
{
	tile->pos = pos;
	tile->chroma = chroma;
	tile->sprite = surf;
	tile->rect = MakeRectBySize( pos, surf->width, surf->height );
	tile->width = surf->width;
	tile->height = surf->height;
}

void DestroyGround( Ground* ground )
{
	free( ground->tiles );
}

void DrawGround(Ground* ground)
{
	Vec2 startPos = ground->pos;
	for ( int i = 0; i < ground->tileCount; i++ )
	{
		DrawSpriteChroma( (int)startPos.x, (int)startPos.y, ground->tiles[i].sprite, ground->tiles[i].chroma );
		startPos.x += ground->tiles[i].width;
	}
}