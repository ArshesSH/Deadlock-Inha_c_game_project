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
		DrawSpriteChroma( 300, 300, &(stage->easyMode), MAGENTA );
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

void UpdateStage( Game* stage, StageType type)
{
	if (type == StageStart)
	{
		if (stage->difficulty == MenuEasy)
		{
			DeleteSizeRect( SurfaceGetRect( &(stage->easyMode) ), 300, 300 );
			DrawSpriteChroma( 300, 300, &(stage->easyMode), MAGENTA );
		}
		else if (stage->difficulty == MenuHard)
		{
			DeleteSizeRect( SurfaceGetRect( &(stage->easyMode) ), 300, 300 );
			DrawSpriteChroma( 300, 300, &(stage->easyMode), MAGENTA );
		}


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

bool IsPlayerInput(int vKey)
{
	return GetAsyncKeyState( vKey ) & 0x8000;
}