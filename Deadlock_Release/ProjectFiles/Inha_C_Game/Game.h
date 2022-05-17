#pragma once

#include "SceneType.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "EndScene.h"

typedef struct game
{
	SceneType stage;

	StartScene startScene;
	SelectScene selectScene;
	StageScene firstScene;
	StageScene secondScene;
	StageScene thirdScene;
	
	EndScene endScene;

	bool IsStageChanged;
	bool IsGameEnd;

}Game;

void MakeStage( Game* stage );

void UpdateModel( Game* stage );

void DrawFrame( Game* game );

void DestroyGame( Game* game );

bool CheckStageChange( SceneType last, SceneType current );


