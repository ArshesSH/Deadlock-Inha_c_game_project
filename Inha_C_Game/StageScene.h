#pragma once

#include "UI.h"
#include "TankPlayer.h"
#include "TankAI.h"
#include "Ground.h"
#include "Turn.h"
#include "PlayerController.h"
#include "SceneType.h"

typedef struct stageScene
{
	SceneType currentScene;
	SceneType nextScene;
	// Turn state
	Turn turn;

	// Player Input
	PlayerInput input;
	Vec2 playerDir;

	// Ground Contents
	Surface tile;
	Ground ground;
	Ground groundAI;

	Vec2 groundStartPos;
	Vec2 groundAIStartPos;

	Color tileChroma;
	int tileCount;
	Rect limitZone;

	// Tank Contents
	TankPlayer playerTank;
	TankAI aiTank;

	// UI
	UI playerUI;
	UI aiUI;

	// Text
	Font guide;
	Font stageMessage;
}StageScene;

void InitStageScene( StageScene* scene, TankType playerTankType, TankType AITankType,
	int difficultOffset, float playerGroundY, float aiGroundY, SceneType cur, SceneType next );

SceneType UpdateStageScene( StageScene* scene);

void DrawStageScene( StageScene* scene );

void DestroyStageScene( StageScene* scene );

void PlayerMoveInput( StageScene* scene );

void UpdateTanksByProjectile( TankModel* pFireTankModel, ProjectileModel* pProjModel, TankModel* pTargetTankModel, Status* pTargetStatus, Turn* turn, Turn desireTurn );
