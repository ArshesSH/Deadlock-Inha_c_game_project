#include "FirstScene.h"

#include "Graphics.h"

#pragma comment(lib,"winmm.lib")
/************************
*		Init Scene		*
*************************/
void InitFirstScene( FirstScene* scene, TankType playerTankType, TankType AITankType, int difficultOffset )
{
	// Generate Ground
	scene->groundStartPos = MakeVec2( 0.0f, 400.0f );
	scene->tileCount = 20;
	scene->tileChroma = MAGENTA;
	MakeSurface( "src/images/GroundTile.bmp", &(scene->tile) );
	MakeFlatGround( &(scene->ground), &(scene->tile), scene->groundStartPos, scene->tileCount, scene->tileChroma );

	// Generate LimitZone
	scene->limitZone = MakeRect( screenHalfWidth - 100, screenHalfWidth + 100, 0, (int)scene->groundStartPos.y );

	// Generate Tank
	MakeTankPlayer( &(scene->playerTank), playerTankType, 30, scene->groundStartPos, scene->limitZone );
	MakeTankAI( &(scene->aiTank), AITankType, 850, scene->groundStartPos, scene->limitZone, difficultOffset );

	// Generate UI
	const Vec2 playerUIPos = MakeVec2( 50, scene->groundStartPos.y + 60 );
	const Vec2 aiUIPos = MakeVec2( 750, scene->groundStartPos.y + 60 );
	MakeUI( &(scene->playerUI), &(scene->playerTank.status), playerUIPos );
	MakeUI( &(scene->aiUI), &(scene->aiTank.status), aiUIPos );

	// Draw First State
	DrawGround( &(scene->ground) );
	DrawTank( &(scene->playerTank.model) );
	DrawTank( &(scene->aiTank.model) );
	DrawPlayerUI( &(scene->playerUI) );
	DrawHealth( &(scene->aiUI) );

	scene->playerDir = MakeVec2( 0.0f, 0.0f );
	scene->turn = PlayerMove;
}


/****************************
*		Update Scene		*
*****************************/
SceneType UpdateFirstScene( FirstScene* scene )
{
	// Turn Player Move
	if ( scene->turn == PlayerMove )
	{
		scene->playerDir.x = 0;
		scene->playerDir.y = 0;
		PlayerMoveInput( scene );
		UpdatePlayerTank( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect );
	}
	// Turn Player Shoot
	else if ( scene->turn == PlayerShoot )
	{
		UpdatePlayerTank( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect );

		// If Player Hit the Target
		if (GetPlayerBulletState( &(scene->playerTank) ) == ProjHit)
		{
			// Change AI State Damaged and Calculate AI Health
			scene->aiTank.model.state = TankDamaged;
			CalcStatusHealth( &(scene->aiTank.status), scene->playerTank.bullet.model.damage );
			SetProjectileWait( &(scene->playerTank.bullet.model));

			scene->playerTank.model.state = TankDrawAndWait;
			scene->turn = AIMove;
		}
		else if (GetPlayerBulletState( &(scene->playerTank) ) == ProjWait)
		{
			scene->playerTank.model.state = TankDrawAndWait;
			scene->turn = AIMove;
		}
	}
	// Turn AI Move
	else if ( scene->turn == AIMove )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect );

		if ( scene->aiTank.model.state == TankFire )
		{
			scene->turn = AIShoot;
		}
	}
	// Turn AI Shoot
	else if ( scene->turn == AIShoot )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect );

		// If Hit target
		if (GetAIBulletState(&(scene->aiTank)) == ProjHit )
		{
			// Play Hit Effect to Player
			scene->playerTank.model.state = TankDamaged;
			PlaySound( TEXT( "src/sounds/explosion.wav" ), NULL, SND_ASYNC );
			scene->playerTank.model.hitPos.x = scene->playerTank.model.pos.x;
			StartEffect( &(scene->playerTank.model.hitEffect) );

			// Calculate Player Health
			CalcStatusHealth( &(scene->playerTank.status), scene->aiTank.bullet.model.damage );
			SetProjectileWait( &(scene->aiTank.bullet.model) );
			scene->aiTank.model.state = TankDrawAndWait;
			scene->turn = PlayerMove;
		}
		// No Hit
		else if (GetAIBulletState( &(scene->aiTank) ) == ProjWait)
		{
			scene->aiTank.model.state = TankDrawAndWait;
			scene->turn = PlayerMove;
		}
	}



	// If player dead, Change to Start Scene
	if ( scene->playerTank.status.statusChange == ActorDead )
	{
		DestroyFirstScene( scene );
		system( "cls" );
		scene->turn = NotInGame;
		return StageStart;
	}
	// If AI Dead Change to Next Scene
	else if (scene->aiTank.status.statusChange == ActorDead )
	{
		DestroyFirstScene( scene );
		system( "cls" );
		scene->turn = NotInGame;
		return Stage2;
	}

	// Update Effect and UI
	UpdateEffect( &(scene->playerTank.model.hitEffect) );
	UpdateEffect( &(scene->aiTank.model.hitEffect) );
	UpdateUI( &(scene->playerUI) );
	UpdateUI( &(scene->aiUI) );

	return Stage1;
}


/************************
*		Draw Scene		*
*************************/
void DrawFirstScene( FirstScene* scene )
{
	if ( scene->turn == PlayerMove )
	{
		DrawUI( &(scene->playerUI) );
	}
	else if ( scene->turn == PlayerShoot )
	{
		DrawProjectilePlayer( &(scene->playerTank.bullet) );
		DrawUI( &(scene->aiUI) );
	}
	else if ( scene->turn == AIMove )
	{
		DrawUI( &(scene->aiUI) );
	}
	else if ( scene->turn == AIShoot )
	{
		DrawProjectileAI( &(scene->aiTank.bullet) );
		DrawUI( &(scene->playerUI) );
	}
	if (scene->turn != NotInGame)
	{
		DrawUI( &(scene->playerUI) );
		DrawUI( &(scene->aiUI) );
		DrawTank( &(scene->playerTank.model) );
		DrawTank( &(scene->aiTank.model) );
	}
}


/****************************
*		Destroy Scene		*
****************************/
/*
*	Destroy List
* 
*	Surface tile;
*	Ground ground;
*	TankPlayer playerTank;
*	TankAI aiTank;
*	UI playerUI;
*	UI aiUI;
*	All 6 Objects
*/
void DestroyFirstScene( FirstScene* scene )
{
	DestroySurface( &(scene->tile) );
	DestroyTankPlayer( &(scene->playerTank) );
	DestroyTankAI( &(scene->aiTank) );
	DestroyGround( &(scene->ground) );
	DestroyUI( &(scene->playerUI) );
	DestroyUI( &(scene->aiUI) );
}


// Player Input Function
void PlayerMoveInput(FirstScene* scene)
{
	// Input Shoot
	if ( IsPlayerInput( VK_SPACE ) )
	{
		scene->turn = PlayerShoot;
		SetTankStateFire( &(scene->playerTank.model) );
		return;
	}

	// Input Move
	if ( IsPlayerInput( VK_RIGHT ) )
	{
		if ( IsTankInMoveZone( scene->playerTank.model.rect, scene->limitZone ) )
		{
			scene->playerDir.x += 1;
			SetTankStateMove( &(scene->playerTank.model) );
		}
	}
	else if ( IsPlayerInput( VK_LEFT ) )
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