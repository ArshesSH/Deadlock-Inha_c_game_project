#pragma once

#include "Ground.h"
#include "Tank.h"
#include "Font.h"

typedef enum difficulty
{
	MenuEasy,
	MenuHard,
	SelectEasy,
	SelectHard
}Difficulty;

typedef enum stageType
{
	StageStart,
	Stage1,
	Stage2,
	Stage3,
	StageEnd
}StageType;

typedef struct game
{
	StageType stage;
	bool IsStageCreated;

	/************************
	*		Stage Start		*
	*************************/
	Font title;
	Surface easyMode;
	Surface hardMode;
	Difficulty difficulty;
	

	Ground ground;
	Tank player;
	Tank ai;
	Font font;
}Game;

void MakeStage( Game* stage, StageType type );
