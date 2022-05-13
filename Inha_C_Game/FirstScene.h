#pragma once

#include "UI.h"
#include "Status.h"
#include "Tank.h"
#include "Ground.h"
#include "Turn.h"
#include "PlayerController.h"
#include "SceneType.h"

typedef struct firstScene
{
	Turn turn;
	PlayerInput input;

	Surface tile;
	Tank playerTank;
	Tank aiTank;
	Ground ground;
	UI playerUI;
	UI aiUI;

	Vec2 playerDir;
	Status playerStatus;
	Status aiStatus;

	Vec2 groundStartPos;
	Color tileChroma;

	int tileCount;
	Rect limitZone;
}FirstScene;

void InitFirstScene( FirstScene* scene, TankType playerTankType );

SceneType UpdateFirstScene( FirstScene* scene );

void DrawFirstScene( FirstScene* scene );

void PlayerMoveInput( FirstScene* scene );
