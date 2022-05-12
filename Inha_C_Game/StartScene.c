#include "StartScene.h"

#include "Graphics.h"
#include <Windows.h>
#include "PlayerController.h"

void InitStartScene(StartScene* scene)
{
	// Make Title and Draw
	MakeFont( &(scene->title), FontLarge );
	const Vec2 titlePos = { 336, 100 };
	DrawFontText( "Last Crew", titlePos, WHITE, &(scene->title) );
	scene->difficulty = MenuEasy;

	MakeSurface( "src/images/easymode.bmp", &(scene->easyMode) );
	MakeSurface( "src/images/hardmode.bmp", &(scene->hardMode) );
	DrawSpriteChroma( 420, 300, &(scene->easyMode), MAGENTA );
}

StageType UpdateStartScene( StartScene* scene )
{
	ChooseDifficulty( &(scene->difficulty) );

	if (scene->difficulty == SelectEasy)
	{
		scene->difficultOffset = 150;
		DestroyStartScene( scene );
		return Stage1;
	}
	else if (scene->difficulty == SelectHard)
	{
		scene->difficultOffset = 100;
		DestroyStartScene( scene );
		return Stage1;
	}
	
	return StageStart;
}

void DrawStartScene( StartScene* scene )
{
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
	DestroySurface( &(scene->easyMode) );
	DestroySurface( &(scene->hardMode) );
}