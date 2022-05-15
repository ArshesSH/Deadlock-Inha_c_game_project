#include "Animation.h"
#include <stdlib.h>
#include "Graphics.h"

void MakeAnimation( Animation* anime, int x, int y, int width, int height, int sectionCount, Surface* s, float holdTime, Color chroma )
{
	anime->curFrame = 0;
	anime->curFrameTime = 0;
	anime->frameHoldTime = holdTime;
	anime->chroma = chroma;
	anime->s = s;
	anime->frameListSize = sectionCount;
	anime->frameList = (Rect*)malloc( sizeof( Rect ) * sectionCount );

	for (int i = 0; i < sectionCount; i++)
	{
		anime->frameList[i] = MakeRect( x + i * width, x + (i + 1) * width, y, y + height );
	}
}

void DrawAnime( Vec2 pos, Animation* anime )
{
	DrawAnimeClip( pos, GetScreenRect(), anime );
}

void DrawAnimeClip(Vec2 pos, Rect clip, Animation* anime)
{
	DrawSpriteClipNonChroma( (int)pos.x, (int)pos.y, anime->frameList[anime->curFrame], clip, anime->s );
}


void DrawAnimeChroma( Vec2 pos, Animation* anime )
{
	DrawAnimeClipChroma( pos, GetScreenRect(), anime );
}

void DrawAnimeClipChroma( Vec2 pos, Rect clip, Animation* anime )
{
	DrawSpriteClipChroma( (int)pos.x, (int)pos.y, anime->frameList[anime->curFrame], clip, anime->s, anime->chroma );
}


void DrawAnimeColor( Vec2 pos, Animation* anime, Color subColor )
{
	DrawAnimeClipColor( pos, GetScreenRect(), anime, subColor );
}

void DrawAnimeClipColor( Vec2 pos, Rect clip, Animation* anime, Color subColor )
{
	DrawSpriteClipSubstitute( (int)pos.x, (int)pos.y, anime->frameList[anime->curFrame], clip, anime->s, anime->chroma, subColor );
}

void UpdateAnimation(Animation* anime, float ft)
{
	anime->curFrameTime += ft;
	while (anime->curFrameTime >= anime->frameHoldTime)
	{
		AdvanceImage( anime );
		anime->curFrameTime -= anime->frameHoldTime;
	}
}

void AdvanceImage(Animation* anime)
{
	if (++(anime->curFrame) >= anime->frameListSize)
	{
		anime->curFrame = 0;
	}
}

void DestroyAnimation(Animation* anime)
{
	free( anime->frameList );
}