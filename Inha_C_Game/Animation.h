#pragma once

#include "Surface.h"

typedef struct animation
{
	Surface* s;
	Color chroma;
	float curFrameTime;
	float frameHoldTime;
	int curFrame;

	// Must free frameList
	Rect* frameList;
	int frameListSize;
}Animation;

void MakeAnimation( Animation* anime, int x, int y, int width, int height, int sectionCount, Surface* s, float holdTime, Color chroma );

void DrawAnime( Vec2 pos, Animation* anime );

void DrawAnimeClip( Vec2 pos, Rect clip, Animation* anime );

void DrawAnimeChroma( Vec2 pos, Animation* anime );

void DrawAnimeClipChroma( Vec2 pos, Rect clip, Animation* anime );

void DrawAnimeColor( Vec2 pos, Animation* anime, Color subColor );

void DrawAnimeClipColor( Vec2 pos, Rect clip, Animation* anime, Color subColor );

void UpdateAnimation( Animation* anime, float ft );

void AdvanceImage( Animation* anime );

void DestroyAnimation( Animation* anime );