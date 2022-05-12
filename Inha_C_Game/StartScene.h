#pragma once

#include "Font.h"
#include "Surface.h"
#include "StageType.h"

typedef enum difficulty
{
	MenuEasy,
	MenuHard,
	SelectEasy,
	SelectHard
}Difficulty;

/************************
*		Stage Start		*
*************************/

typedef struct startScene
{
	Font title;
	Surface easyMode;
	Surface hardMode;
	Difficulty difficulty;
	int difficultOffset;
}StartScene;

void InitStartScene( StartScene* scene );

StageType UpdateStartScene( StartScene* scene );

void DrawStartScene( StartScene* scene );

void ChooseDifficulty( Difficulty* current );

void DestroyStartScene( StartScene* scene );
