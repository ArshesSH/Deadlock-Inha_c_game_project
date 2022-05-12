#include "Game.h"

#include <Windows.h>
#include "Graphics.h"
void MakeStage( Game* stage, StageType type )
{

	if (type == StageStart)
	{
		// Make Title and Draw
		MakeFont( &(stage->title), FontLarge );
		const Vec2 titlePos = { 336, 100 };
		DrawFontText( "Last Crew", titlePos, WHITE, &(stage->title) );
		stage->difficulty = MenuEasy;

		MakeSurface( "src/images/easymode.bmp", &(stage->easyMode) );
		MakeSurface( "src/images/hardmode.bmp", &(stage->hardMode) );
		DrawSpriteChroma( 420, 300, &(stage->easyMode), MAGENTA );
	}
	else if (type == Stage1)
	{

	}
	else if (type == Stage2)
	{

	}
	else if (type == Stage3)
	{

	}
	else if (type == StageEnd)
	{

	}

}

void UpdateModel( Game* game )
{
	if (game->stage == StageStart)
	{
		ChooseDifficulty( &(game->difficulty) );

		if (game->difficulty == MenuEasy)
		{
			if (WasSurfaceDrew( &(game->hardMode) ))
			{
				DeleteSurfaceScreen( &(game->hardMode), 420, 300 );
				DrawSpriteChroma( 420, 300, &(game->easyMode), MAGENTA );
			}

		}
		else if (game->difficulty == MenuHard)
		{
			if (WasSurfaceDrew( &(game->easyMode) ))
			{
				DeleteSurfaceScreen( &(game->easyMode), 420, 300 );
				DrawSpriteChroma( 420, 300, &(game->hardMode), MAGENTA );
			}
		}
		else if (game->difficulty == SelectEasy)
		{
			game->difficultOffset = 150;
			game->stage = Stage1;
		}
		else if (game->difficulty == SelectHard)
		{
			game->difficultOffset = 100;
			game->stage = Stage1;
		}
	}
	else if (game->stage == Stage1)
	{

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

void DrawFrame( Game* game )
{

}


void ChooseDifficulty(Difficulty* current)
{
	if (IsPlayerInput( VK_LEFT ) || IsPlayerInput(VK_RIGHT))
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

bool IsPlayerInput(int vKey)
{
	return GetAsyncKeyState( vKey ) & 0x8000;
}