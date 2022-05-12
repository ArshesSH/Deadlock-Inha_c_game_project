#pragma once

#include "Ground.h"
#include "Tank.h"
#include "Font.h"
#include "SceneType.h"
#include "StartScene.h"

typedef struct game
{
	SceneType stage;

	StartScene startScene;

	bool IsStageChanged;

}Game;

void MakeStage( Game* stage );

void UpdateModel( Game* stage );

void DrawFrame( Game* game );

bool CheckStageChange( SceneType last, SceneType current );


