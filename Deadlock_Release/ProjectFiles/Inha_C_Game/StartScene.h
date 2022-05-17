#pragma once

#include "Font.h"
#include "Surface.h"
#include "SceneType.h"

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
	Font keyGuide;
	Font loading;
	Vec2 loadingPos;
	Surface startImage;
	Surface easyMode;
	Surface hardMode;
	Difficulty difficulty;
	int difficultOffset;
}StartScene;

void InitStartScene( StartScene* scene );

SceneType UpdateStartScene( StartScene* scene );

void DrawStartScene( StartScene* scene );

void ChooseDifficulty( Difficulty* current );

void DestroyStartScene( StartScene* scene );
