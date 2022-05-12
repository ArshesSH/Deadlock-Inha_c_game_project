#include "FirstScene.h"

void InitFirstStage( FirstScene* scene )
{
	// Generate Ground
	scene->groundStartPos = MakeVec2( 0.0f, 300.0f );
	scene->tileCount = 20;
	scene->tileChroma = MAGENTA;
	MakeSurface( "src/images/GroundTile.bmp", &(scene->tile) );
	MakeFlatGround( &(scene->ground), &(scene->tile), scene->groundStartPos, scene->tileCount, scene->tileChroma );

	//Generate 
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