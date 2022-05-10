#pragma once

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