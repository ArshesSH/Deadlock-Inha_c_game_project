#include "StartScene.h"

#include "Graphics.h"
#include <Windows.h>
#include "PlayerController.h"

void InitStartScene(StartScene* scene)
{
	// Make Title and Draw
	MakeFont( &(scene->title), FontLarge );
	const Vec2 titlePos = { 350, 100 };
	DrawFontText( "Deadlock", titlePos, WHITE, &(scene->title) );
	scene->difficulty = MenuEasy;

	MakeSurface( "src/images/Background.bmp", &(scene->startImage) );
	MakeSurface( "src/images/easymode.bmp", &(scene->easyMode) );
	MakeSurface( "src/images/hardmode.bmp", &(scene->hardMode) );
	DrawSpriteNonChroma( 415, 200, &(scene->startImage) );
	DrawSpriteChroma( 420, 300, &(scene->easyMode), MAGENTA );
}

SceneType UpdateStartScene( StartScene* scene )
{
	ChooseDifficulty( &(scene->difficulty) );

	SceneType choosedScene = StageStart;
	switch (scene->difficulty)
	{
	case SelectEasy:
		scene->difficultOffset = 150;
		DestroyStartScene( scene );
		choosedScene = StageSelectTank;
		break;
		
	case SelectHard:
		scene->difficultOffset = 100;
		DestroyStartScene( scene );
		choosedScene = StageSelectTank;
		break;

	default:
		choosedScene = StageStart;
		break;
	}
	return choosedScene;

	/*
	* Old If Statement
	* 
	if (scene->difficulty == SelectEasy)
	{
		scene->difficultOffset = 150;
		DestroyStartScene( scene );
		return StageSelectTank;
	}
	else if (scene->difficulty == SelectHard)
	{
		scene->difficultOffset = 100;
		DestroyStartScene( scene );
		return StageSelectTank;
	}
	
	return StageStart;
	*/
}

void DrawStartScene( StartScene* scene )
{
	switch (scene->difficulty)
	{
	case MenuEasy:
		if (WasSurfaceDrew( &(scene->hardMode) ))
		{
			DeleteSurfaceScreen( &(scene->hardMode), 420, 300 );
			DrawSpriteChroma( 420, 300, &(scene->easyMode), MAGENTA );
		}
		break;

	case MenuHard:
		if (WasSurfaceDrew( &(scene->easyMode) ))
		{
			DeleteSurfaceScreen( &(scene->easyMode), 420, 300 );
			DrawSpriteChroma( 420, 300, &(scene->hardMode), MAGENTA );
		}
		break;

	default:
		break;
	}

	/*
	* Old ifstatement
	* 
	if (scene->difficulty == MenuEasy)
	{
		if (WasSurfaceDrew( &(scene->hardMode) ))
		{
			DeleteSurfaceScreen( &(scene->hardMode), 420, 300 );
			DrawSpriteChroma( 420, 300, &(scene->easyMode), MAGENTA );
		}

	}
	else if (scene->difficulty == MenuHard)
	{
		if (WasSurfaceDrew( &(scene->easyMode) ))
		{
			DeleteSurfaceScreen( &(scene->easyMode), 420, 300 );
			DrawSpriteChroma( 420, 300, &(scene->hardMode), MAGENTA );
		}
	}
	*/
}

void ChooseDifficulty( Difficulty* current )
{
	if (IsPlayerInput( VK_LEFT ) || IsPlayerInput( VK_RIGHT ))
	{
		if (*current == MenuEasy)
		{
			*current = MenuHard;
		}
		else if (*current == MenuHard)
		{
			*current = MenuEasy;
		}
	}
	if (IsPlayerInput( VK_RETURN ))
	{
		if (*current == MenuEasy)
		{
			*current = SelectEasy;
		}
		else if (*current == MenuHard)
		{
			*current = SelectHard;
		}
	}
}

void DestroyStartScene(StartScene* scene)
{
	DestroyFont( &(scene->title) );
	DestroySurface( &(scene->startImage) );
	DestroySurface( &(scene->easyMode) );
	DestroySurface( &(scene->hardMode) );
	system( "cls" );
}