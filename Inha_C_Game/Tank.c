#include "Tank.h"

#include "Graphics.h"
#include <stdlib.h>

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos )
{
	tank->type = type;
	switch ( type )
	{
	case LightTank:
		MakeSurface( "src/images/tank/player/LightTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case MiddleTank:
		MakeSurface( "src/images/tank/player/MiddleTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case MiddleTankAI:
		MakeSurface( "src/images/tank/ai/MiddleTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	default:
		break;
	}

	tank->pos.x = (float)pos_x;
	tank->pos.y = groundPos.y - tank->sprite.height;
	
	tank->gunPos.x += tank->pos.x;
	tank->gunPos.y = tank->pos.y;

	MakeProjectile( &(tank->bullet), tank->gunPos, &(tank->bulletSprite), MAGENTA );

	tank->rect = MakeRectBySize( tank->pos, tank->sprite.width, tank->sprite.height );
	tank->lastRect = tank->rect;

	tank->state = TankWait;
}

void UpdateTankPlayer( Tank* tank, Rect ground, Vec2 dir, int angle, int power )
{
	if ( tank->state == TankMove )
	{
		MoveTank( tank, dir );
		tank->state = TankWait;
	}
	else if ( tank->state == TankFire )
	{
		if ( tank->bullet.state == ProjWait )
		{
			SetProjectile( &(tank->bullet), tank->gunPos );
			SetProjectilePlayer( &(tank->bullet), angle, power );
			SetProjectileStateFire( &(tank->bullet) );
		}
		else if ( tank->bullet.state == ProjFire )
		{
			if ( IsNextProjectileInScreen( &(tank->bullet) ) )
			{
				UpdateProjectilePlayer( &(tank->bullet) );
				if ( IsOverlapWithTarget( &(tank->bullet), ground ) )
				{
					EndProjectile( &(tank->bullet), tank->gunPos );
					tank->state = TankWait;
				}
			}
			else
			{
				EndProjectile( &(tank->bullet), tank->gunPos );
				tank->state = TankWait;
			}
		}
	}
}

void UpdateTankAI( Tank* tank, Rect ground, Vec2 userPos, int aiDiffOffset )
{
	if ( tank->state == TankMove )
	{
		if ( aiMaxCount <= 10 )
		{
			MoveTankAI( tank );
			aiMaxCount++;
		}
		else
		{
			tank->state = TankWait;
		}
	}
	else if ( tank->state == TankFire )
	{
		if ( tank->bullet.state == ProjWait )
		{
			SetProjectile( &(tank->bullet), tank->gunPos );
			SetProjectileAI( &(tank->bullet), userPos, tank->gunPos, aiDiffOffset );
			SetProjectileStateFire( &(tank->bullet) );
		}
		else if ( tank->bullet.state == ProjFire )
		{
			if ( IsNextProjectileInScreen( &(tank->bullet) ) )
			{
				UpdatePrjectileAI( &(tank->bullet) );
				if ( IsOverlapWithTarget( &(tank->bullet), ground ) )
				{
					EndProjectile( &(tank->bullet), tank->gunPos );
					tank->state = TankWait;
				}
			}
			else
			{
				EndProjectile( &(tank->bullet), tank->gunPos );
				tank->state = TankWait;
			}
		}
	}
}



void MoveTank( Tank* tank, Vec2 dir )
{
	const Vec2 vel = Vec2Mul( dir, (float)tank->speed );
	const Vec2 nextPos = Vec2Add( (tank->pos), vel );
	const Rect nextRect = MakeRectBySize( nextPos, tank->sprite.width, tank->sprite.height );

	tank->lastRect = tank->rect;

	// Screen Check
	if ( RectIsContainedBy( nextRect, GetScreenRect() ) )
	{
		tank->pos = nextPos;
		tank->rect = nextRect;
		Vec2AddEqual( &(tank->gunPos), vel );
	}
}

void SetTankAIStateMove( Tank* tank )
{
	aiCount = 0;
	aiMaxCount = rand() % 10;

	// Create -1 or 1
	aiDir = ((rand() % 2) * -2) + 1;
	tank->state = TankMove;
}

void SetTankPlayerStateMove( Tank* tank )
{
	tank->state = TankMove;
}

void MoveTankAI( Tank* tank )
{
	MoveTank( tank, MakeVec2( (float)aiDir, 0.0f ) );
}

void SetTankStateFire( Tank* tank )
{
	tank->state = TankFire;
}


bool IsTankOverlapWith(Tank* tank, Rect target)
{
	return RectIsOverlappingWith( tank->rect, target );
}

void DrawTank( Tank* tank )
{
	if ( tank->state == TankWait )
	{
		DeleteRect( tank->lastRect );
		DrawTankOnce( tank );
		tank->state = TankDrawAndWait;
	}
	else if ( tank->state == TankMove )
	{
		DeleteRect( tank->lastRect );
		DrawSpriteNonChroma( (int)tank->pos.x, (int)tank->pos.y, &(tank->sprite) );
	}
	else if ( tank->state == TankFire )
	{
		if ( tank->bullet.state == ProjFire )
		{
			DrawProjectileChroma( &(tank->bullet) );
			Sleep( 20 );
			//DeleteRect( tank->bullet.rect );
		}
	}
}

void DrawTankOnce( Tank* tank )
{
	DrawSpriteNonChroma( (int)tank->pos.x, (int)tank->pos.y, &(tank->sprite) );
}