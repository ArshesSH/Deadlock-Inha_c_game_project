#include "Game.h"

#include <Windows.h>
#include "Graphics.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void MakeStage( Game* game )
{
	switch (game->stage)
	{
	case StageStart:
		PlaySound( TEXT( "src/sounds/BackgroundMusic.wav" ), NULL, SND_ASYNC );
		InitStartScene( &(game->startScene) );
		break;

	case StageSelectTank:
		InitSelectScene( &(game->selectScene) );
		break;

	case Stage1:
		PlaySound( NULL, NULL, SND_ASYNC );
		InitFirstScene( &(game->firstScene), game->selectScene.playerSelection, MRLAI, game->startScene.difficultOffset );
		break;

	case Stage2:
		InitFirstScene( &(game->firstScene), game->selectScene.playerSelection, MRLAI, game->startScene.difficultOffset );
		break;

	case Stage3:
		break;

	case StageEnd:
		
		break;

	case GameEnd:
		break;
	}
}

void UpdateModel( Game* game )
{
	const SceneType lastState = game->stage;

	switch (game->stage)
	{
	case StageStart:
		game->stage = UpdateStartScene( &(game->startScene) );
		break;

	case StageSelectTank:
		game->stage = UpdateSelectScene( &(game->selectScene) );
		break;

	case Stage1:
		game->stage = UpdateFirstScene( &(game->firstScene) );
		break;

	case Stage2:
		break;

	case Stage3:
		break;

	case StageEnd:
		break;

	case GameEnd:
		game->IsGameEnd = true;
		return;
		break;
	}
	// Check Game Stage change
	game->IsStageChanged = CheckStageChange(lastState, game->stage);
}

void DrawFrame( Game* game )
{

	switch (game->stage)
	{
	case StageStart:
		DrawStartScene( &(game->startScene) );
		break;
	case StageSelectTank:
		DrawSelectScene( &(game->selectScene) );
		break;
	case Stage1:
		DrawFirstScene( &(game->firstScene) );
		break;
	case Stage2:
		break;
	case Stage3:
		break;
	case StageEnd:
		break;
	case GameEnd:
		break;
	}
}

void DestroyGame(Game* game)
{
	switch (game->stage)
	{
	case StageStart:
		DestroyStartScene( &(game->startScene) );
		break;
	case StageSelectTank:
		DestroySelectScene( &(game->selectScene) );
		break;
	case Stage1:
		DestroyFirstScene( &(game->firstScene) );
		break;
	case Stage2:
		break;
	case Stage3:
		break;
	case StageEnd:
		DestroyEndScene( &(game->endScene) )
		break;
	case GameEnd:
		break;
	}
}


bool CheckStageChange( SceneType last, SceneType current )
{
	return last != current;
}