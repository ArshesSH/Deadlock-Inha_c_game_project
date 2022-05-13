#include "FirstScene.h"

void InitFirstScene( FirstScene* scene, TankType playerTankType )
{
	// Generate Ground
	scene->groundStartPos = MakeVec2( 0.0f, 400.0f );
	scene->tileCount = 20;
	scene->tileChroma = MAGENTA;
	MakeSurface( "src/images/GroundTile.bmp", &(scene->tile) );
	MakeFlatGround( &(scene->ground), &(scene->tile), scene->groundStartPos, scene->tileCount, scene->tileChroma );

	// Generate Tank
	MakeTank( &(scene->playerTank), playerTankType, 30, scene->groundStartPos );
	MakeTank( &(scene->aiTank), MediumTankAI, 850, scene->groundStartPos );

	// Generate Status
	MakeStatus( &(scene->playerStatus), scene->playerTank.tankMaxHealth, scene->playerTank.tankMinAngle,
		scene->playerTank.tankMinPower, scene->playerTank.tankSpeed );
	MakeStatus( &(scene->aiStatus), scene->aiTank.tankMaxHealth, 0, 0, scene->aiTank.tankSpeed );

	// Generate UI
	const Vec2 playerUIPos = MakeVec2( 50, scene->groundStartPos.y + 60 );
	const Vec2 aiUIPos = MakeVec2( 750, scene->groundStartPos.y + 60 );
	MakeUI( &(scene->playerUI), &(scene->playerStatus), playerUIPos );
	MakeUI( &(scene->aiUI), &(scene->aiStatus), aiUIPos );

	// Draw First State
	DrawGround( &(scene->ground) );
	DrawTank( &(scene->playerTank) );
	DrawTank( &(scene->aiTank) );
	DrawPlayerUI( &(scene->playerUI) );
	DrawHealth( &(scene->aiUI) );
}

void UpdateFirstStage( FirstScene* scene )
{

}

void DrawFirstStage( FirstScene* scene )
{

}

void DestroyFirstStage( FirstScene* scene )
{

}