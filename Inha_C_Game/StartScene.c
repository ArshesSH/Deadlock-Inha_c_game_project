#include "StartScene.h"

#include "Graphics.h"
#include <Windows.h>
#include "PlayerController.h"

void InitStartScene(StartScene* scene)
{
	MakeSurface( "src/images/BackgroundSrc.bmp", &(scene->startImage) );
	DrawSpriteTitle( 0,0, &(scene->startImage) );

	// Make Title and Draw
	MakeFont( &(scene->title), FontLarge );
	// 8 chars are 256width, middle is screenwidth / 2 + 128
	const float yAlign = (float)(screenHeight / 5.4);
	const Vec2 titlePos = { (float)(screenHalfWidth - 128), yAlign };
	DrawFontText( "Deadlock", titlePos, WHITE, &(scene->title) );
	scene->difficulty = MenuEasy;

	MakeFont( &(scene->loading), FontLarge );
	scene->loadingPos = MakeVec2( (float)(screenHalfWidth - 128), titlePos.y + 65 );


	// Create Bacground and select menu
	//MakeSurface( "src/images/Background.bmp", &(scene->startImage) );
	MakeSurface( "src/images/easy.bmp", &(scene->easyMode) );
	MakeSurface( "src/images/hard.bmp", &(scene->hardMode) );
	//DrawSpriteNonChroma( (screenHalfWidth - (scene->startImage.width / 2) ), titlePos.y + yAlign, &(scene->startImage) );
	DrawSpriteChroma( 420, titlePos.y + (yAlign) * 2, &(scene->easyMode), BLACK );

	MakeFont( (&scene->keyGuide), FontSmall );
	const Vec2 guidePos = { (float)(screenHalfWidth - 108),titlePos.y + (yAlign) * 3 };
	DrawFontText( "Press Enter to Select\n\nPress L or R to change mode", guidePos, LIGHTGRAY, &(scene->keyGuide) );
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
	DrawFontText( "Loading...", scene->loadingPos, GREEN, &(scene->loading) );
	DestroyFont( &(scene->title) );
	DestroyFont( &(scene->keyGuide) );
	DestroyFont( &(scene->loading) );
	DestroySurface( &(scene->startImage) );
	DestroySurface( &(scene->easyMode) );
	DestroySurface( &(scene->hardMode) );
	system( "cls" );
}