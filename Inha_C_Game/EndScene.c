#include "EndScene.h"

#include "Graphics.h"

void InitEndScene( EndScene* scene )
{
	MakeFont( &(scene->title), FontLarge );
	float yOffset = screenHeight / 5.4;
	Vec2 titlePos = { (float)(screenHalfWidth - 256), yOffset };
	DrawFontText( "Congratulations!", titlePos, MakeRGB( 0, 84, 255 ), &(scene->title) );

	MakeFont( &(scene->script), FontMedium );
	Vec2 titlePos = { (float)(screenHalfWidth - 200), yOffset * 3 };
	DrawFontText( "Now you are free to go...", titlePos, WHITE, &(scene->script) );

	MakeFont( &(scene->guide), FontSmall );
	Vec2 titlePos = { (float)(screenHalfWidth - 108), yOffset * 4 };
	DrawFontText( "Press Enter to restart Game\nPress Esc to Quit Game", titlePos, WHITE, &(scene->guide) );
}

SceneType UpdateEndScene( EndScene* scene )
{
	if (IsPlayerInput( VK_RETURN ))
	{
		return StageStart;
	}
	else if (IsPlayerInput( VK_ESCAPE ))
	{
		return GameEnd;
	}
}

void DestroyEndScene( EndScene* scene )
{
	DestroyFont( &(scene->title) );
	DestroyFont( &(scene->script) );
	DestroyFont( &(scene->guide) );
}