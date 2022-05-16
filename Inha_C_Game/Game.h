#pragma once

#include "SceneType.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "FirstScene.h"
#include "EndScene.h"

typedef struct game
{
	SceneType stage;

	StartScene startScene;
	SelectScene selectScene;
	FirstScene firstScene;

	EndScene endScene;

	bool IsStageChanged;
	bool IsGameEnd;

}Game;

void MakeStage( Game* stage );

void UpdateModel( Game* stage );

void DrawFrame( Game* game );

bool CheckStageChange( SceneType last, SceneType current );


