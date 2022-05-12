#pragma once

#include "Ground.h"
#include "Tank.h"
#include "Font.h"
#include "StageType.h"
#include "StartScene.h"

typedef struct game
{
	StageType stage;

	StartScene startScene;

	bool IsStageChanged;

}Game;

void MakeStage( Game* stage );

void UpdateModel( Game* stage );

void DrawFrame( Game* game );

bool CheckStageChange( StageType last, StageType current );


