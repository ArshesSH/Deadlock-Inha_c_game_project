#pragma once

#include "UI.h"
#include "Status.h"
#include "TankPlayer.h"
#include "TankAI.h"
#include "Ground.h"
#include "Turn.h"
#include "PlayerController.h"
#include "SceneType.h"

typedef struct firstScene
{
	Turn turn;
	PlayerInput input;

	Surface tile;
	TankPlayer playerTank;
	TankAI aiTank;
	Ground ground;

	UI playerUI;
	UI aiUI;


	Vec2 playerDir;

	Vec2 groundStartPos;
	Color tileChroma;

	int tileCount;
	Rect limitZone;
}FirstScene;

void InitFirstScene( FirstScene* scene, TankType playerTankType, int difficultOffset );

SceneType UpdateFirstScene( FirstScene* scene);

void DrawFirstScene( FirstScene* scene );

void DestroyFirstScene( FirstScene* scene );

void PlayerMoveInput( FirstScene* scene );
