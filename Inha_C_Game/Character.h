#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Animation.h"

typedef enum sequence
{
	WalkLeft,
	WalkRight,
	WalkUp,
	WalkDown,
	StandLeft,
	StandRight,
	StandUp,
	StandDown,
	Count
}Sequence;

typedef struct character
{
	Surface sprite;
	Vec2 pos;
	Vec2 vel;
	Sequence curSequence;
	Color chroma;
	float holdTime;
	int speed;

	// Must free animations and animation's rect list
	Animation* animations;

}Character;

void MakeCharacter( Character* character, Vec2 pos, int spriteStartX, int spriteStartY, int width, int height, int sectionCount, Color chroma, const char* filename );

void DrawCharacter( Character* chara );

void SetCharacterDirection( Character* chara, Vec2 dir );

void UpdateCharacter( Character* chara, float dt );

void DestroyCharacter( Character* character );
