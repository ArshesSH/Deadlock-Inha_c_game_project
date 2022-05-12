#pragma once

#include "Font.h"
#include "Surface.h"
#include "Tank.h"
#include "Ground.h"

typedef struct firstStage
{
	Font ui;
	Surface tile;
	Vec2 groundStartPos;
	Ground ground;
	Color tileChroma;
	Tank player;
	Tank ai;

	int tileCount;

}FirstStage;