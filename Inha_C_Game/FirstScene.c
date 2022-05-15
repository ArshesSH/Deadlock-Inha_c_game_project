#include "FirstScene.h"

#include "Graphics.h"

// Init First Stage
void InitFirstScene( FirstScene* scene, TankType playerTankType, int difficultOffset )
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
	MakeTankAI( &(scene->aiTank), MediumTankAI, 850, scene->groundStartPos, scene->limitZone, difficultOffset );
	//MakeTank( &(scene->playerTank), playerTankType, 30, scene->groundStartPos );
	//MakeTank( &(scene->aiTank), MediumTankAI, 850, scene->groundStartPos );

	// Generate Status
	/*
	MakeStatus( &(scene->playerStatus), scene->playerTank.tankMaxHealth, scene->playerTank.tankMinAngle,
		scene->playerTank.tankMinPower, scene->playerTank.tankSpeed );
	MakeStatus( &(scene->aiStatus), scene->aiTank.tankMaxHealth, 0, 0, scene->aiTank.tankSpeed );
	*/

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

SceneType UpdateFirstScene( FirstScene* scene )
{
	// Turn Player Move
	if ( scene->turn == PlayerMove )
	{
		scene->playerDir.x = 0;
		scene->playerDir.y = 0;
		PlayerMoveInput( scene );
		UpdatePlayerTank( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect );
		//UpdateTankPlayer( &(scene->playerTank), scene->aiTank.rect, scene->ground.rect, scene->playerDir, scene->playerStatus.angle, scene->playerStatus.power, scene->limitZone );
		//UpdateUI( &(scene->playerUI) );
	}
	// Turn Player Shoot
	else if ( scene->turn == PlayerShoot )
	{
		UpdatePlayerTank( &(scene->playerTank), scene->playerDir, scene->aiTank.model.rect, scene->ground.rect );
		//UpdateTankPlayer( &(scene->playerTank), scene->aiTank.rect, scene->ground.rect, scene->playerDir, scene->playerStatus.angle, scene->playerStatus.power, scene->limitZone );
		if (GetPlayerBulletState( &(scene->playerTank) ) == ProjHit)
		{
			CalcStatusHealth( &(scene->aiTank.status), scene->playerTank.bullet.model.damage );
			//UpdateUI( &(scene->aiUI) );
			
			SetProjectileWait( &(scene->playerTank.bullet.model));
			//scene->aiTank.model.state = TankDamaged;
			scene->playerTank.model.state = TankDrawAndWait;

			scene->turn = AIMove;
		}
		else if (GetPlayerBulletState( &(scene->playerTank) ) == ProjWait)
		{
			scene->turn = AIMove;
		}
		
		//if ( scene->playerTank.model.state == TankDrawAndWait )
		//{
		//	scene->turn = AIMove;
		//}
	}
	else if ( scene->turn == AIMove )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect );
		//UpdateTankAI( &(scene->aiTank), scene->playerTank.rect, scene->ground.rect, scene->playerTank.pos, difficultOffset, scene->limitZone );

		if ( scene->aiTank.model.state == TankFire )
		{
			scene->turn = AIShoot;
		}
	}
	else if ( scene->turn == AIShoot )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.model.pos, scene->playerTank.model.rect, scene->ground.rect );

		// If Hit target
		if (GetAIBulletState(&(scene->aiTank)) == ProjHit )
		{
			CalcStatusHealth( &(scene->playerTank.status), scene->aiTank.bullet.model.damage );
			SetProjectileWait( &(scene->aiTank.bullet.model) );

			scene->turn = PlayerMove;
		}
		else if (GetAIBulletState( &(scene->aiTank) ) == ProjWait)
		{
			scene->turn = PlayerMove;
		}
		//if (scene->aiTank.model.state == TankDrawAndWait )
		//{
		//	scene->turn = PlayerMove;
		//}
	}

	if ( scene->playerTank.status.statusChange == ActorDead )
	{
		DestroyFirstScene( scene );
		return StageStart;
	}
	else if (scene->aiTank.status.statusChange == ActorDead )
	{
		DestroyFirstScene( scene );
		return Stage2;
	}

	UpdateUI( &(scene->playerUI) );
	UpdateUI( &(scene->aiUI) );
	return Stage1;
}

void DrawFirstScene( FirstScene* scene )
{
	if ( scene->turn == PlayerMove )
	{
		DrawTank( &(scene->playerTank.model) );
		DrawUI( &(scene->playerUI) );
	}
	else if ( scene->turn == PlayerShoot )
	{
		DrawTank( &(scene->playerTank.model) );
		DrawProjectilePlayer( &(scene->playerTank.bullet) );
		DrawUI( &(scene->aiUI) );
	}
	else if ( scene->turn == AIMove )
	{
		DrawTank( &(scene->aiTank.model) );
		DrawUI( &(scene->aiUI) );
	}
	else if ( scene->turn == AIShoot )
	{
		DrawTank( &(scene->aiTank.model) );
		DrawProjectileAI( &(scene->aiTank.bullet) );
		DrawUI( &(scene->playerUI) );
	}


}

void DestroyFirstScene( FirstScene* scene )
{
	DestroySurface( &(scene->tile) );
	DestroyTank( &(scene->playerTank.model) );
	DestroyTank( &(scene->aiTank.model) );
	DestroyGround( &(scene->ground) );
	DestroyUI( &(scene->playerUI) );
	DestroyUI( &(scene->aiUI) );
}

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
		if ( IsTankInMoveZone( &(scene->playerTank.model) ) )
		{
			scene->playerDir.x += 1;
			SetTankStateMove( &(scene->playerTank.model) );
		}
	}
	else if ( IsPlayerInput( VK_LEFT ) )
	{
		if (IsTankInMoveZone( &(scene->playerTank.model) ))
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