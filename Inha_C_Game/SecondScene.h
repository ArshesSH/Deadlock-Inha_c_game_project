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

	// Key Guide
	Font guide;
}SecondScene;
