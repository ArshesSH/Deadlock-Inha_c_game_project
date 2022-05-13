#include "Game.h"

#include <Windows.h>
#include "Graphics.h"


void MakeStage( Game* game )
{
	if (game->stage == StageStart)
	{
		InitStartScene( &(game->startScene) );
	}
	else if (game->stage == StageSelectTank)
	{
		InitSelectScene( &(game->selectScene) );
	}
	else if (game->stage == Stage1)
	{
		InitFirstScene( &(game->firstScene), game->selectScene.playerSelection );
	}
	else if (game->stage == Stage2)
	{

	}
	else if (game->stage == Stage3)
	{

	}
	else if (game->stage == StageEnd)
	{

	}

}

void UpdateModel( Game* game )
{
	const SceneType lastState = game->stage;

	if (game->stage == StageStart)
	{
		game->stage = UpdateStartScene( &(game->startScene) );
	}
	else if (game->stage == StageSelectTank)
	{
		game->stage = UpdateSelectScene( &(game->selectScene) );
	}
	else if (game->stage == Stage1)
	{
		game->stage = UpdateFirstScene( &(game->firstScene), game->startScene.difficultOffset );
	}
	else if (game->stage == Stage2)
	{

	}
	else if (game->stage == Stage3)
	{

	}
	else if (game->stage == StageEnd)
	{

	}

	game->IsStageChanged = CheckStageChange(lastState, game->stage);
}

void DrawFrame( Game* game )
{
	if (game->stage == StageStart)
	{
		DrawStartScene( &(game->startScene) );
	}
	else if (game->stage == StageSelectTank)
	{
		DrawSelectScene( &(game->selectScene) );
	}
	else if (game->stage == Stage1)
	{
		DrawFirstScene( &(game->firstScene) );
	}
	else if (game->stage == Stage2)
	{

	}
	else if (game->stage == Stage3)
	{

	}
	else if (game->stage == StageEnd)
	{

	}
}

bool CheckStageChange( SceneType last, SceneType current )
{
	return last != current;
}