#pragma once

#include "UI.h"
#include "TankPlayer.h"
#include "TankAI.h"
#include "Ground.h"
#include "Turn.h"
#include "PlayerController.h"
#include "SceneType.h"

typedef struct secondScene
{
	// Turn state
	Turn turn;

	// Player Input
	PlayerInput input;
	Vec2 playerDir;

	// Ground Contents
	Surface tile;
	Ground ground;
	Vec2 groundStartPos;
	Color tileChroma;
	int tileCount;
	Rect limitZone;

	// Tank Contents
	TankPlayer playerTank;
	TankAI aiTank;

	// UI
	UI playerUI;
	UI aiUI;
}SecondScene;

void InitSecondScene( SecondScene* scene, TankType playerTankType, int difficultOffset );

SceneType UpdateSecondScene( SecondScene* scene );

void DrawSecondScene( SecondScene* scene );

void DestroySecondScene( SecondScene* scene );

void PlayerMoveInput( SecondScene* scene );
