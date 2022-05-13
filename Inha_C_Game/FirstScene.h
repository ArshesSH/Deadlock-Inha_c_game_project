#pragma once

#include "UI.h"
#include "Status.h"
#include "Tank.h"
#include "Ground.h"

typedef struct firstScene
{
	Surface tile;
	Tank playerTank;
	Tank aiTank;
	Ground ground;
	UI playerUI;
	UI aiUI;

	Status playerStatus;
	Status aiStatus;

	Vec2 groundStartPos;
	Color tileChroma;

	int tileCount;
}FirstScene;

void InitFirstScene( FirstScene* scene, TankType playerTankType );
