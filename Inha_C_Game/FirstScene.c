#include "FirstScene.h"

#include "Graphics.h"

// Init First Stage
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

	scene->limitZone = MakeRect( screenHalfWidth - 100, screenHalfWidth + 100, 0, scene->groundStartPos.y );

	// Draw First State
	DrawGround( &(scene->ground) );
	DrawTank( &(scene->playerTank) );
	DrawTank( &(scene->aiTank) );
	DrawPlayerUI( &(scene->playerUI) );
	DrawHealth( &(scene->aiUI) );

	scene->playerDir = MakeVec2( 0.0f, 0.0f );

	scene->turn = PlayerMove;
}

SceneType UpdateFirstScene( FirstScene* scene, int difficultOffset )
{
	if ( scene->turn == PlayerMove )
	{
		scene->playerDir.x = 0;
		scene->playerDir.y = 0;
		PlayerMoveInput( scene );
		UpdateTankPlayer( &(scene->playerTank), scene->aiTank.rect, scene->ground.rect, scene->playerDir, scene->playerStatus.angle, scene->playerStatus.power, scene->limitZone );
		UpdateUI( &(scene->playerUI) );
	}
	else if ( scene->turn == PlayerShoot )
	{
		UpdateTankPlayer( &(scene->playerTank), scene->aiTank.rect, scene->ground.rect, scene->playerDir, scene->playerStatus.angle, scene->playerStatus.power, scene->limitZone );
		if ( scene->playerTank.bullet.state == ProjHit )
		{
			CalcStatusHealth( &(scene->aiStatus), scene->playerTank.bullet.damage );
			UpdateUI( &(scene->aiUI) );
			SetProjectileStateWait( &(scene->playerTank.bullet) );

			scene->playerTank.state = TankDrawAndWait;
			//scene->turn = AIMove;
			//SetTankAIStateMove( &(scene->aiTank) );
		}
		
		if ( scene->playerTank.state == TankDrawAndWait )
		{
			scene->turn = AIMove;
			SetTankAIStateMove( &(scene->aiTank) );
		}
	}
	else if ( scene->turn == AIMove )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.rect, scene->ground.rect, scene->playerTank.pos, difficultOffset, scene->limitZone );

		if ( scene->aiTank.state == TankDrawAndWait )
		{
			scene->turn = AIShoot;
			SetTankStateFire( &(scene->aiTank) );
		}
	}
	else if ( scene->turn == AIShoot )
	{
		UpdateTankAI( &(scene->aiTank), scene->playerTank.rect, scene->ground.rect, scene->playerTank.pos, difficultOffset, scene->limitZone );
		if ( scene->aiTank.bullet.state == ProjHit )
		{
			CalcStatusHealth( &(scene->playerStatus), scene->aiTank.bullet.damage );
			UpdateUI( &(scene->playerUI) );
			SetProjectileStateWait( &(scene->aiTank.bullet) );
			scene->turn = PlayerMove;
		}

		if ( scene->aiTank.state == TankDrawAndWait )
		{
			scene->turn = PlayerMove;
		}
	}

	if ( &(scene->playerStatus) == ActorDead )
	{
		DestroyFirstScene( scene );
		return StageStart;
	}
	else if ( &(scene->aiStatus) == ActorDead )
	{
		DestroyFirstScene( scene );
		return Stage2;
	}

	return Stage1;
}

void DrawFirstScene( FirstScene* scene )
{
	if ( scene->turn == PlayerMove )
	{
		DrawTank( &(scene->playerTank) );
		DrawUI( &(scene->playerUI) );
	}
	else if ( scene->turn == PlayerShoot )
	{
		DrawTank( &(scene->playerTank) );
	}
	else if ( scene->turn == AIMove )
	{
		DrawTank( &(scene->aiTank) );
		DrawUI( &(scene->aiUI) );
	}
	else if ( scene->turn == AIShoot )
	{
		DrawTank( &(scene->aiTank) );
		DrawUI( &(scene->playerUI) );
	}
}

void DestroyFirstScene( FirstScene* scene )
{
	DestroySurface( &(scene->tile) );
	DestroyTank( &(scene->playerTank) );
	DestroyTank( &(scene->aiTank) );
	DestroyGround( &(scene->ground) );
	DestroyUI( &(scene->playerUI) );
	DestroyUI( &(scene->aiUI) );
}

void PlayerMoveInput(FirstScene* scene)
{
	// Input Shoot
	if ( IsPlayerInput( VK_RETURN ) )
	{
		scene->turn = PlayerShoot;
		SetTankStateFire( &(scene->playerTank) );
		return;
	}

	// Input Move
	if ( IsPlayerInput( VK_RIGHT ) )
	{
		if ( IsTankInMoveZone( scene->playerTank.rect, scene->limitZone ) )
		{
			scene->playerDir.x += 1;
			scene->playerTank.state = TankMove;
		}
	}
	else if ( IsPlayerInput( VK_LEFT ) )
	{
		if ( IsTankInMoveZone( scene->playerTank.rect, scene->limitZone ) )
		{
			scene->playerDir.x -= 1;
			scene->playerTank.state = TankMove;
		}
	}

	// Input angle
	if ( IsPlayerInput( VK_UP ) )
	{
		SetStatusAngle( &(scene->playerStatus), min( ++(scene->playerStatus.angle), scene->playerTank.tankMaxAngle ) );
	}
	else if ( IsPlayerInput( VK_DOWN ) )
	{
		SetStatusAngle( &(scene->playerStatus), max( --(scene->playerStatus.angle), scene->playerTank.tankMinAngle ) );
	}

	// Input Power
	if ( IsPlayerInput( VK_SHIFT ) )
	{
		SetStatusPower( &(scene->playerStatus), min( ++(scene->playerStatus.power), scene->playerTank.tankMaxPower ) );
	}
	else if ( IsPlayerInput( VK_CONTROL ) )
	{
		SetStatusPower( &(scene->playerStatus), max( --(scene->playerStatus.power), scene->playerTank.tankMinPower ) );
	}
}