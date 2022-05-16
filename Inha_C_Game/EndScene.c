#include "EndScene.h"

#include "Graphics.h"

void InitEndScene( EndScene* scene )
{
	MakeFont( &(scene->title), FontLarge );
	Vec2 titlePos = { (float)(screenHalfWidth - 256), screenYOffset };
	DrawFontText( "Congratulations!", titlePos, MakeRGB( 0, 84, 255 ), &(scene->title) );

	MakeFont( &(scene->script), FontMedium );
	Vec2 scriptPos = { (float)(screenHalfWidth - 200), screenYOffset * 3 };
	DrawFontText( "Now you are free to go...", scriptPos, WHITE, &(scene->script) );

	MakeFont( &(scene->guide), FontSmall );
	Vec2 guidePos = { (float)(screenHalfWidth - 108), screenYOffset * 4 };
	DrawFontText( "Press Enter to restart Game\nPress Esc to Quit Game", guidePos, WHITE, &(scene->guide) );
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
	return StageEnd;
}

void DestroyEndScene( EndScene* scene )
{
	DestroyFont( &(scene->title) );
	DestroyFont( &(scene->script) );
	DestroyFont( &(scene->guide) );
	system( "cls" );
}