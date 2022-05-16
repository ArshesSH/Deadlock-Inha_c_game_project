#include "SelectScene.h"

#include "Graphics.h"
#include "PlayerController.h"

// Initialize Select Scene, This should load once when Scene Changed.
void InitSelectScene( SelectScene* scene )
{
	// Create Font
	MakeFont( &(scene->title), FontMedium );
	MakeFont( &(scene->discription), FontSmall );
	const Vec2 titlePos = { 340, 50 };
	DrawFontText( "Select Your Tank!", titlePos, GREEN, &(scene->title) );
	scene->tankType = LightTank;
	MakeSurface( "src/images/tank/player/LightTankGray50.bmp", &(scene->light) );
	MakeSurface( "src/images/tank/player/MediumTankGray50.bmp", &(scene->medium) );
	MakeSurface( "src/images/tank/player/HeavyTankGray50.bmp", &(scene->heavy) );
	MakeSurface( "src/images/tank/player/MRLGray50.bmp", &(scene->mrl) );

	// Create Tank
	const int offset = -100;
	scene->posLight = MakeVec2( (float)(screenHalfWidth - (scene->light.width / 2)),
		(float)(screenHalfHeight - (scene->light.height / 2) + offset) );
	scene->posMedium = MakeVec2( (float)(screenHalfWidth - (scene->medium.width / 2)),
		(float)(screenHalfHeight - (scene->medium.height / 2) + offset ));
	scene->posHeavy = MakeVec2( (float)(screenHalfWidth - (scene->heavy.width / 2)),
		(float)(screenHalfHeight - (scene->heavy.height / 2) + offset ));
	scene->posMRL = MakeVec2( (float)(screenHalfWidth - (scene->mrl.width / 2)),
		(float)(screenHalfHeight - (scene->mrl.height / 2) + offset ));
	scene->posDisc = MakeVec2( 250.0f, (float)screenHalfHeight );
	DrawSpriteNonChroma( (int)scene->posLight.x, (int)scene->posLight.y, &(scene->light) );
	DrawFontText( textLight, scene->posDisc, WHITE, &(scene->discription) );
}

// Update Select Scene.
SceneType UpdateSelectScene( SelectScene* scene )
{
	ChooseTank( &(scene->tankType) );

	SceneType chooseScene = StageSelectTank;
	switch (scene->tankType)
	{
	case SelectLightTank:
		scene->playerSelection = LightTank;
		DestroySelectScene( scene );
		chooseScene = Stage1;
		break;

	case SelectMediumTank:
		scene->playerSelection = MediumTank;
		DestroySelectScene( scene );
		chooseScene = Stage1;
		break;

	case SelectHeavyTank:
		scene->playerSelection = HeavyTank;
		DestroySelectScene( scene );
		chooseScene = Stage1;
		break;

	case SelectMRL:
		scene->playerSelection = MRL;
		DestroySelectScene( scene );
		chooseScene = Stage1;
		break;

	default:
		chooseScene = StageSelectTank;
		break;
	}
	return chooseScene;

	/*
	if ( scene->tankType == SelectLightTank )
	{
		scene->playerSelection = LightTank;
		DestroySelectScene( scene );
		return Stage1;
	}
	else if ( scene->tankType == SelectMediumTank )
	{
		scene->playerSelection = MediumTank;
		DestroySelectScene( scene );
		return Stage1;
	}
	else if ( scene->tankType == SelectHeavyTank )
	{
		scene->playerSelection = HeavyTank;
		DestroySelectScene( scene );
		return Stage1;
	}
	else if ( scene->tankType == SelectMRL )
	{
		scene->playerSelection = MRL;
		DestroySelectScene( scene );
		return Stage1;
	}

	return StageSelectTank;
	*/
}

void DrawSelectScene( SelectScene* scene )
{
	switch (scene->tankType)
	{
	case LightTank:
		if (WasSurfaceDrew( &(scene->mrl) ))
		{
			DeleteSurfaceScreen( &(scene->mrl), (int)scene->posMRL.x, (int)scene->posMRL.y );
			DrawSpriteNonChroma( (int)scene->posLight.x, (int)scene->posLight.y, &(scene->light) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textLight, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if (WasSurfaceDrew( &(scene->medium) ))
		{
			DeleteSurfaceScreen( &(scene->medium), (int)scene->posMedium.x, (int)scene->posMedium.y );
			DrawSpriteNonChroma( (int)scene->posLight.x, (int)scene->posLight.y, &(scene->light) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textLight, scene->posDisc, WHITE, &(scene->discription) );
		}
		break;

	case MediumTank:
		if (WasSurfaceDrew( &(scene->light) ))
		{
			DeleteSurfaceScreen( &(scene->light), (int)scene->posLight.x, (int)scene->posLight.y );
			DrawSpriteNonChroma( (int)scene->posMedium.x, (int)scene->posMedium.y, &(scene->medium) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMedium, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if (WasSurfaceDrew( &(scene->heavy) ))
		{
			DeleteSurfaceScreen( &(scene->heavy), (int)scene->posHeavy.x, (int)scene->posHeavy.y );
			DrawSpriteNonChroma( (int)scene->posMedium.x, (int)scene->posMedium.y, &(scene->medium) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMedium, scene->posDisc, WHITE, &(scene->discription) );
		}
		break;

	case HeavyTank:
		if (WasSurfaceDrew( &(scene->medium) ))
		{
			DeleteSurfaceScreen( &(scene->medium), (int)scene->posMedium.x, (int)scene->posMedium.y );
			DrawSpriteNonChroma( (int)scene->posHeavy.x, (int)scene->posHeavy.y, &(scene->heavy) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textHeavy, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if (WasSurfaceDrew( &(scene->mrl) ))
		{
			DeleteSurfaceScreen( &(scene->mrl), (int)scene->posMRL.x, (int)scene->posMRL.y );
			DrawSpriteNonChroma( (int)scene->posHeavy.x, (int)scene->posHeavy.y, &(scene->heavy) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textHeavy, scene->posDisc, WHITE, &(scene->discription) );
		}
		break;

	case MRL:
		if (WasSurfaceDrew( &(scene->heavy) ))
		{
			DeleteSurfaceScreen( &(scene->heavy), (int)scene->posHeavy.x, (int)scene->posHeavy.y );
			DrawSpriteNonChroma( (int)scene->posMRL.x, (int)scene->posMRL.y, &(scene->mrl) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMRL, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if (WasSurfaceDrew( &(scene->light) ))
		{
			DeleteSurfaceScreen( &(scene->light), (int)scene->posLight.x, (int)scene->posLight.y );
			DrawSpriteNonChroma( (int)scene->posMRL.x, (int)scene->posMRL.y, &(scene->mrl) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMRL, scene->posDisc, WHITE, &(scene->discription) );
		}
		break;

	default:
		break;
	}


	/*
	if ( scene->tankType == LightTank )
	{
		if ( WasSurfaceDrew( &(scene->mrl) ) )
		{
			DeleteSurfaceScreen( &(scene->mrl), (int)scene->posMRL.x, (int)scene->posMRL.y );
			DrawSpriteNonChroma( (int)scene->posLight.x, (int)scene->posLight.y, &(scene->light) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textLight, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if ( WasSurfaceDrew( &(scene->medium) ) )
		{
			DeleteSurfaceScreen( &(scene->medium), (int)scene->posMedium.x, (int)scene->posMedium.y );
			DrawSpriteNonChroma( (int)scene->posLight.x, (int)scene->posLight.y, &(scene->light) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textLight, scene->posDisc, WHITE, &(scene->discription) );
		}
	}
	else if ( scene->tankType == MediumTank )
	{
		if ( WasSurfaceDrew( &(scene->light) ) )
		{
			DeleteSurfaceScreen( &(scene->light), (int)scene->posLight.x, (int)scene->posLight.y );
			DrawSpriteNonChroma( (int)scene->posMedium.x, (int)scene->posMedium.y, &(scene->medium) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMedium, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if ( WasSurfaceDrew( &(scene->heavy) ) )
		{
			DeleteSurfaceScreen( &(scene->heavy), (int)scene->posHeavy.x, (int)scene->posHeavy.y );
			DrawSpriteNonChroma( (int)scene->posMedium.x, (int)scene->posMedium.y, &(scene->medium) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMedium, scene->posDisc, WHITE, &(scene->discription) );
		}
	}
	else if ( scene->tankType == HeavyTank )
	{
		if ( WasSurfaceDrew( &(scene->medium) ) )
		{
			DeleteSurfaceScreen( &(scene->medium), (int)scene->posMedium.x, (int)scene->posMedium.y );
			DrawSpriteNonChroma( (int)scene->posHeavy.x, (int)scene->posHeavy.y, &(scene->heavy) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textHeavy, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if ( WasSurfaceDrew( &(scene->mrl) ) )
		{
			DeleteSurfaceScreen( &(scene->mrl), (int)scene->posMRL.x, (int)scene->posMRL.y );
			DrawSpriteNonChroma( (int)scene->posHeavy.x, (int)scene->posHeavy.y, &(scene->heavy) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textHeavy, scene->posDisc, WHITE, &(scene->discription) );
		}
	}
	else if ( scene->tankType == MRL )
	{
		if ( WasSurfaceDrew( &(scene->heavy) ) )
		{
			DeleteSurfaceScreen( &(scene->heavy), (int)scene->posHeavy.x, (int)scene->posHeavy.y );
			DrawSpriteNonChroma( (int)scene->posMRL.x, (int)scene->posMRL.y, &(scene->mrl) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMRL, scene->posDisc, WHITE, &(scene->discription) );
		}
		else if ( WasSurfaceDrew( &(scene->light) ) )
		{
			DeleteSurfaceScreen( &(scene->light), (int)scene->posLight.x, (int)scene->posLight.y );
			DrawSpriteNonChroma( (int)scene->posMRL.x, (int)scene->posMRL.y, &(scene->mrl) );
			DeleteRect( scene->discription.textRect );
			DrawFontText( textMRL, scene->posDisc, WHITE, &(scene->discription) );
		}
	}
	*/
}

void DestroySelectScene( SelectScene* scene )
{
	DestroyFont( &(scene->title) );
	DestroyFont( &(scene->discription) );
	DestroySurface( &(scene->light) );
	DestroySurface( &(scene->medium) );
	DestroySurface( &(scene->heavy) );
	DestroySurface( &(scene->mrl) );
	system( "cls" );
}

// Choose Tank type in SelectScene by user kbd Input
void ChooseTank( TankType* current )
{
	if (IsPlayerInput( VK_RIGHT ))
	{
		switch (*current)
		{
		case LightTank:
			*current = MediumTank;
			break;
		case MediumTank:
			*current = HeavyTank;
			break;
		case HeavyTank:
			*current = MRL;
			break;
		case MRL:
			*current = LightTank;
			break;
		}
		/*
		if (*current == LightTank)
		{
			*current = MediumTank;
		}
		else if (*current == MediumTank)
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
		*/
	}
	else if (IsPlayerInput( VK_LEFT ))
	{
		switch (*current)
		{
		case LightTank:
			*current = MRL;
			break;
		case MediumTank:
			*current = LightTank;
			break;
		case HeavyTank:
			*current = MediumTank;
			break;
		case MRL:
			*current = HeavyTank;
			break;
		}

		/*
		if (*current == LightTank)
		{
			*current = MRL;
		}
		else if (*current == MediumTank)
		{
			*current = LightTank;
		}
		else if (*current == HeavyTank)
		{
			*current = MediumTank;
		}
		else if (*current == MRL)
		{
			*current = HeavyTank;
		}
		*/
	}

	if (IsPlayerInput( VK_RETURN ))
	{
		switch (*current)
		{
		case LightTank:
			*current = SelectLightTank;
			break;
		case MediumTank:
			*current = SelectMediumTank;
			break;
		case HeavyTank:
			*current = SelectHeavyTank;
			break;
		case MRL:
			*current = SelectMRL;
			break;
		}

		/*
		if (*current == LightTank)
		{
			*current = SelectLightTank;
		}
		else if (*current == MediumTank)
		{
			*current = SelectMediumTank;
		}
		else if (*current == HeavyTank)
		{
			*current = SelectHeavyTank;
		}
		else if (*current == MRL)
		{
			*current = SelectMRL;
		}
		*/
	}
}