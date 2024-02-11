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
		InitStageScene( &(game->firstScene), game->selectScene.playerSelection, LightTankAI, game->startScene.difficultOffset, 400, 400, Stage1, Stage2 );
		break;

	case Stage2:
		PlaySound( NULL, NULL, SND_ASYNC );
		InitStageScene( &(game->secondScene), game->selectScene.playerSelection, MediumTankAI, game->startScene.difficultOffset, 400, 353, Stage2, Stage3 );
		break;

	case Stage3:
		PlaySound( NULL, NULL, SND_ASYNC );
		InitStageScene( &(game->thirdScene), game->selectScene.playerSelection, HeavyTankAI, game->startScene.difficultOffset, 353, 400, Stage3, StageEnd );
		break;

	case StageEnd:
		PlaySound( TEXT( "src/sounds/gameend.wav" ), NULL, SND_ASYNC );
		InitEndScene( &(game->endScene) );
		break;

	case GameEnd:
		game->IsGameEnd = true;
		return;
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
		game->stage = UpdateStageScene( &(game->firstScene) );
		break;

	case Stage2:
		game->stage = UpdateStageScene( &(game->secondScene) );
		break;

	case Stage3:
		game->stage = UpdateStageScene( &(game->thirdScene) );
		break;

	case StageEnd:
		game->stage = UpdateEndScene( &(game->endScene) );
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
		DrawStageScene( &(game->firstScene) );
		break;
	case Stage2:
		DrawStageScene( &(game->secondScene) );
		break;
	case Stage3:
		DrawStageScene( &(game->thirdScene) );
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
		DestroyStageScene( &(game->firstScene) );
		break;
	case Stage2:
		DestroyStageScene( &(game->secondScene) );
		break;
	case Stage3:
		DestroyStageScene( &(game->thirdScene) );
		break;
	case StageEnd:
		system( "cls" );
		DestroyEndScene( &(game->endScene) );
		break;
	}
}


bool CheckStageChange( SceneType last, SceneType current )
{
	return last != current;
}