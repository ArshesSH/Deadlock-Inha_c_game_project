#include "StageScene.h"

#include "Graphics.h"
#include <stdlib.h>

/************************
*		Init Scene		*
*************************/
void InitStageScene( StageScene* scene, TankType playerTankType, TankType AITankType,
	int difficultOffset, float playerGroundY, float aiGroundY, SceneType cur, SceneType next )
{
	// Make Stage text
	MakeFont( &(scene->stageMessage), FontLarge );
	char stageStr[20];
	sprintf_s( stageStr, 20, "Stage %d", cur - 1 );
	DrawFontText( stageStr, MakeVec2( (float)(screenHalfWidth - 112), screenYOffset * 2 ), GREEN, &(scene->stageMessage) );
	scene->currentScene = cur;
	scene->nextScene = next;
	const Vec2 guidePos = { (float)(screenHalfWidth - 140), screenHalfHeight + screenYOffset * 2 };

	// Generate Ground
	const int groundCounts = 10;

	MakeSurface( "src/images/GroundTile.bmp", &(scene->tile) );
	scene->groundStartPos = MakeVec2( 0.0f, playerGroundY );
	scene->groundAIStartPos = MakeVec2( (float)(scene->tile.width) * groundCounts, aiGroundY );
	scene->tileCount = groundCounts;
	scene->tileChroma = MAGENTA;

	MakeFlatGround( &(scene->ground), &(scene->tile), scene->groundStartPos, scene->tileCount, scene->tileChroma );
	MakeFlatGround( &(scene->groundAI), &(scene->tile), scene->groundAIStartPos, scene->tileCount, scene->tileChroma );

	// Generate LimitZone
	scene->limitZone = MakeRect( screenHalfWidth - (int)screenXOffset, screenHalfWidth + (int)screenXOffset, 0, (int)scene->groundStartPos.y );
	MakeFont( &(scene->guide), FontSmall );

	// Generate Tank
	const int playerX = rand() % 100 + 20;
	const int aiX = screenWidth - 50 - rand() % 100;
	MakeTankPlayer( &(scene->playerTank), playerTankType, playerX, scene->groundStartPos, scene->limitZone );
	MakeTankAI( &(scene->aiTank), AITankType, aiX, scene->groundAIStartPos, scene->limitZone, difficultOffset );

	// Generate UI
	const Vec2 playerUIPos = MakeVec2( screenXOffset / 2, (screenYOffset * 4) + (screenYOffset / 2) + 10 );
	const Vec2 aiUIPos = MakeVec2( screenWidth - screenXOffset * 2, (screenYOffset * 4) + (screenYOffset / 2) + 10 );
	MakeUI( &(scene->playerUI), &(scene->playerTank.status), playerUIPos );
	MakeUI( &(scene->aiUI), &(scene->aiTank.status), aiUIPos );

	// Draw First State
	DrawGround( &(scene->ground) );
	DrawGround( &(scene->groundAI) );
	DrawTank( &(scene->playerTank.model) );
	DrawTank( &(scene->aiTank.model) );
	DrawPlayerUI( &(scene->playerUI) );
	DrawHealth( &(scene->aiUI) );
	DrawFontText( "Press L or R to Move\nPress Up or Down to change Angle\nPress Shift or Ctrl to change Power\nPress Spacebar to Fire",
		guidePos, LIGHTGRAY, &(scene->guide) );

	DeleteRect( scene->stageMessage.textRect );

	scene->playerDir = MakeVec2( 0.0f, 0.0f );
	scene->turn = PlayerMove;
}


/****************************
*		Update Scene		*
*****************************/
SceneType UpdateStageScene( StageScene* scene )
{
	switch (scene->turn)
	{
	case PlayerMove:
		// Reset Direction
		scene->playerDir.x = 0;
		scene->playerDir.y = 0;
		
		// Get Player Input
		PlayerMoveInput( scene );

		// Update Player Tank (Move unitl Fire)
		UpdateTankPlayer( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect, scene->groundAI.rect);
		break;

	case PlayerShoot:
		// Update Player Tank ( and Update projectile )
		UpdateTankPlayer( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect, scene->groundAI.rect);

		// Update Hit Effect and Status by Projectile Status
		UpdateTanksByProjectile( &(scene->playerTank.model), &(scene->playerTank.bullet.model), &(scene->aiTank.model),
			&(scene->aiTank.status), &(scene->turn), AIMove );
		break;

	case AIMove:
		// Update AI Tank (Move)
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect, scene->groundAI.rect);
		if (scene->aiTank.model.state == TankFire)
		{
			scene->turn = AIShoot;
		}
		break;

	case AIShoot:
		// Update AI Tank (projectile)
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect, scene->groundAI.rect );

		// Update Hit Effect and Status by Projectile Status
		UpdateTanksByProjectile( &(scene->aiTank.model), &(scene->aiTank.bullet.model), &(scene->playerTank.model),
			&(scene->playerTank.status), &(scene->turn), PlayerMove );
		break;
	}

	// If player dead, Change to Start Scene
	if ( scene->playerTank.status.statusChange == ActorDead )
	{
		DestroyStageScene( scene );
		system( "cls" );
		scene->turn = NotInGame;
		return StageStart;
	}
	// If AI Dead Change to Next Scene
	else if (scene->aiTank.status.statusChange == ActorDead )
	{
		DestroyStageScene( scene );
		system( "cls" );
		scene->turn = NotInGame;
		return scene->nextScene;
	}

	// Update Effect and UI
	UpdateEffect( &(scene->playerTank.model.hitEffect) );
	UpdateEffect( &(scene->aiTank.model.hitEffect) );
	UpdateUI( &(scene->playerUI) );
	UpdateUI( &(scene->aiUI) );

	return scene->currentScene;
}


/************************
*		Draw Scene		*
*************************/
void DrawStageScene( StageScene* scene )
{
	if (scene->turn >= PlayerMove && scene->turn<= AIShoot)
	{
		DrawUI( &(scene->playerUI) );
		DrawUI( &(scene->aiUI) );
		DrawTank( &(scene->playerTank.model) );
		DrawTank( &(scene->aiTank.model) );
		DrawProjectilePlayer( &(scene->playerTank.bullet) );
		DrawProjectileAI( &(scene->aiTank.bullet) );
	}
}


/****************************
*		Destroy Scene		*
****************************/
void DestroyStageScene( StageScene* scene )
{
	DestroyFont( &(scene->guide) );
	DestroySurface( &(scene->tile) );
	DestroyTankPlayer( &(scene->playerTank) );
	DestroyTankAI( &(scene->aiTank) );
	DestroyGround( &(scene->ground) );
	DestroyGround( &(scene->groundAI) );
	DestroyUI( &(scene->playerUI) );
	DestroyUI( &(scene->aiUI) );
}


// Player Input Function
void PlayerMoveInput(StageScene* scene)
{
	// Input Shoot
	if ( IsPlayerInput( VK_SPACE ) )
	{
		scene->turn = PlayerShoot;
		SetTankStateFire( &(scene->playerTank.model) );
		return;
	}

	// Input Move
	if (IsPlayerInput( VK_RIGHT ))
	{
		if (IsTankInMoveZone( scene->playerTank.model.rect, scene->limitZone ))
		{
			scene->playerDir.x += 1;
			SetTankStateMove( &(scene->playerTank.model) );
		}
	}
	else if (IsPlayerInput( VK_LEFT ))
	{
		if (IsTankInMoveZone( scene->playerTank.model.rect, scene->limitZone ))
		{
			scene->playerDir.x -= 1;
			SetTankStateMove( &(scene->playerTank.model) );
		}
	}
	else
	{
		scene->playerTank.model.state = TankDrawAndWait;
	}



	// Input angle
	if ( IsPlayerInput( VK_UP ) )
	{
		SetStatusAngle( &(scene->playerTank.status), min( (scene->playerTank.status.angle)++, scene->playerTank.model.tankMaxAngle ) );
	}
	else if ( IsPlayerInput( VK_DOWN ) )
	{
		SetStatusAngle( &(scene->playerTank.status), max( (scene->playerTank.status.angle)--, scene->playerTank.model.tankMinAngle ) );
	}

	// Input Power
	if ( IsPlayerInput( VK_SHIFT ) )
	{
		SetStatusPower( &(scene->playerTank.status), min( (scene->playerTank.status.power)++, scene->playerTank.model.tankMaxPower ) );
	}
	else if ( IsPlayerInput( VK_CONTROL ) )
	{
		SetStatusPower( &(scene->playerTank.status), max( (scene->playerTank.status.power)--, scene->playerTank.model.tankMinPower ) );
	}
}


void UpdateTanksByProjectile( TankModel* pFireTankModel, ProjectileModel* pProjModel, TankModel* pTargetTankModel, Status* pTargetStatus, Turn* turn, Turn desireTurn)
{
	// If  Hit the Target
	switch (pProjModel->state)
	{
	case ProjHit:
		// Play effects
		PlaySound( TEXT( "src/sounds/explosion.wav" ), NULL, SND_ASYNC );
		pTargetTankModel->hitPos.x = pTargetTankModel->pos.x;
		StartEffect( &(pTargetTankModel->hitEffect) );

		// Change Target State Damaged and Calculate AI Health
		CalcStatusHealth( pTargetStatus, pProjModel->damage );
		SetProjectileWait( pProjModel );
		pFireTankModel->state = TankDrawAndWait;
		*turn = desireTurn;
		break;

	case ProjWait:
		pFireTankModel->state = TankDrawAndWait;
		*turn = desireTurn;
		break;
	}
}