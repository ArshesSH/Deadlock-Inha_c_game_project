#include "SelectScene.h"

#include "PlayerController.h"

void InitSelectScene( SelectScene* scene )
{
	MakeFont( &(scene->title), FontMiddle );
	MakeFont( &(scene->discription), FontSmall );
	const Vec2 titlePos = { 340, 50 };
	DrawFontText( "Select Your Tank!", titlePos, GREEN, &(scene->title) );
}

SceneType UpdateSelectStage( SelectScene* scene )
{
	ChooseDifficulty( &(scene->tankType) );
	
}

void DrawSelectStage( SelectScene* scene )
{

}

void DestroySelectStage( SelectScene* scene )
{

}

void ChooseDifficulty( TankType* current )
{
	if (IsPlayerInput( VK_RIGHT ))
	{
		if (*current == LightTank)
		{
			*current = MiddleTank;
		}
		else if (*current == MiddleTank)
		{
			*current = HeavyTank;
		}
		else if (*current == HeavyTank)
		{
			*current = MRL;
		}
		else if (*current == MRL)
		{
			*current = LightTank;
		}
	}
	else if (IsPlayerInput( VK_LEFT ))
	{
		if (*current == LightTank)
		{
			*current = MRL;
		}
		else if (*current == MiddleTank)
		{
			*current = LightTank;
		}
		else if (*current == HeavyTank)
		{
			*current = MiddleTank;
		}
		else if (*current == MRL)
		{
			*current = HeavyTank;
		}
	}

	if (IsPlayerInput( VK_RETURN ))
	{
		if (*current == LightTank)
		{
			*current = SelectLightTank;
		}
		else if (*current == MiddleTank)
		{
			*current = SelectMiddleTank;
		}
		else if (*current == HeavyTank)
		{
			*current = SelectHeavyTank;
		}
		else if (*current == MRL)
		{
			*current = SelectMRL;
		}
	}
}