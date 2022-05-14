#include "Tank.h"

#include "Graphics.h"
#include <stdlib.h>
#include <Windows.h>

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos )
{
	tank->type = type;
	switch ( type )
	{
	case LightTank:
		MakeSurface( "src/images/tank/player/LightTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet1.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 10;
		tank->tankMaxHealth = 100;
		tank->tankMaxAngle = 20;
		tank->tankMinAngle = 10;
		tank->tankMaxPower = 100;
		tank->tankMinPower = 40;
		tank->bullet.damage = 10;
		tank->gunPosYOffset = 5;
		tank->gunPos.x = (float)tank->sprite.width;
		tank->firePosXOffset = 0;
		break;
	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet1.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 10;
		tank->tankMaxHealth = 100;
		tank->bullet.damage = 10;
		tank->gunPos.x = 0.0f;
		tank->gunPosYOffset = 5;
		tank->firePosXOffset = -tank->fireEffect.sprite.width;
		break;
	case MediumTank:
		MakeSurface( "src/images/tank/player/MediumTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 5;
		tank->tankMaxHealth = 150;
		tank->tankMaxAngle = 22;
		tank->tankMinAngle = 10;
		tank->tankMaxPower = 120;
		tank->tankMinPower = 40;
		tank->bullet.damage = 20;
		tank->gunPosYOffset = 5;
		tank->gunPos.x = (float)tank->sprite.width;
		tank->firePosXOffset = 0;
		break;
	case MediumTankAI:
		MakeSurface( "src/images/tank/ai/MediumTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 5;
		tank->tankMaxHealth = 150;
		tank->bullet.damage = 20;
		tank->gunPos.x = 0.0f;
		tank->gunPosYOffset = 5;
		tank->firePosXOffset = -tank->fireEffect.sprite.width;
		break;
	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 1;
		tank->tankMaxHealth = 200;
		tank->tankMaxAngle = 35;
		tank->tankMinAngle = 10;
		tank->tankMaxPower = 120;
		tank->tankMinPower = 40;
		tank->bullet.damage = 30;
		tank->gunPosYOffset = -2;
		tank->gunPos.x = (float)tank->sprite.width;
		tank->firePosXOffset = 0;
		break;
	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 1;
		tank->tankMaxHealth = 200;
		tank->bullet.damage = 30;
		tank->gunPos.x = 0.0f;
		tank->gunPosYOffset = -2;
		tank->firePosXOffset = -tank->fireEffect.sprite.width;
		break;
	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bulletFire.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire2.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 3;
		tank->tankMaxHealth = 80;
		tank->tankMaxAngle = 75;
		tank->tankMinAngle = 50;
		tank->tankMaxPower = 150;
		tank->tankMinPower = 40;
		tank->bullet.damage = 50;
		tank->gunPosYOffset = -10;
		tank->gunPos.x = (float)tank->sprite.width;
		tank->firePosXOffset = 0;
		break;
	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip30.bmp", &(tank->sprite) );
		MakeSurface( "src/images/bulletFire.bmp", &(tank->bulletSprite) );
		MakeEffect( &(tank->fireEffect), "src/images/fire2Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		tank->tankSpeed = 3;
		tank->tankMaxHealth = 80;
		tank->bullet.damage = 50;
		tank->gunPos.x = 0.0f;
		tank->gunPosYOffset = 0;
		tank->firePosXOffset = -tank->fireEffect.sprite.width;
		break;
	default:
		break;
	}

	tank->pos.x = (float)pos_x;
	tank->pos.y = groundPos.y - tank->sprite.height;
	
	tank->gunPos.x += tank->pos.x;
	tank->gunPos.y = tank->pos.y + tank->gunPosYOffset;

	MakeProjectile( &(tank->bullet), tank->gunPos, &(tank->bulletSprite), MAGENTA );
	MakeEffect( &(tank->hitEffect), "src/images/fire3.bmp", MAGENTA, "src/coin.wav", 1.0f );

	tank->rect = MakeRectBySize( tank->pos, tank->sprite.width, tank->sprite.height );
	tank->lastRect = tank->rect;
	tank->nextRect = tank->rect;
	tank->fireEffectCenterY = (tank->fireEffect.sprite.height / 2) + tank->pos.y + tank->gunPosYOffset;

	tank->state = TankWait;
}

void UpdateTankPlayer( Tank* tank, Rect targetTankRect, Rect ground, Vec2 dir, int angle, int power, Rect limitZone )
{
	if ( tank->state == TankMove )
	{
		MoveTank( tank, dir, limitZone );
		tank->state = TankWait;
	}
	else if ( tank->state == TankFire )
	{
		if ( tank->bullet.state == ProjWait )
		{
			SetProjectile( &(tank->bullet), tank->gunPos );
			SetProjectilePlayer( &(tank->bullet), angle, power );
			SetProjectileStateFire( &(tank->bullet) );
			StartEffect( &(tank->fireEffect) );
		}
		else if ( tank->bullet.state == ProjFire )
		{
			UpdateEffect( &(tank->fireEffect) );
			if ( IsNextProjectileInScreen( &(tank->bullet) ) )
			{
				UpdateProjectilePlayer( &(tank->bullet) );

				// Hit Target(AI)
				if ( IsOverlapWithTarget( &(tank->bullet), targetTankRect ) )
				{
					SetProjectileStateHit( &(tank->bullet) );
					StartEffect( &(tank->hitEffect) );
				}

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

void UpdateTankAI( Tank* tank, Rect targetTankRect, Rect ground, Vec2 userPos, int aiDiffOffset, Rect limitZone )
{
	if ( tank->state == TankMove )
	{
		if ( aiMaxCount <= 10 )
		{
			MoveTankAI( tank, limitZone );
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
			StartEffect( &(tank->fireEffect) );
		}
		else if ( tank->bullet.state == ProjFire )
		{
			UpdateEffect( &(tank->fireEffect) );
			if ( IsNextProjectileInScreen( &(tank->bullet) ) )
			{
				UpdatePrjectileAI( &(tank->bullet) );

				// Hit Target(Player)
				if ( IsOverlapWithTarget( &(tank->bullet), targetTankRect ) )
				{
					SetProjectileStateHit( &(tank->bullet) );
				}

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



void MoveTank( Tank* tank, Vec2 dir, Rect limitZone )
{
	const Vec2 vel = Vec2Mul( dir, (float)tank->tankSpeed );
	const Vec2 nextPos = Vec2Add( (tank->pos), vel );
	tank->nextRect = MakeRectBySize( nextPos, tank->sprite.width, tank->sprite.height );

	tank->lastRect = tank->rect;

	// Screen Check
	if ( IsTankInMoveZone( tank->nextRect, limitZone) )
	{
		tank->pos = nextPos;
		tank->rect = tank->nextRect;
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

void MoveTankAI( Tank* tank, Rect limitZone )
{
	MoveTank( tank, MakeVec2( (float)aiDir, 0.0f ), limitZone );
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
		const Vec2 fireEffectPos = { tank->gunPos.x + tank->firePosXOffset, tank->fireEffectCenterY };
		DrawEffect( &(tank->fireEffect), fireEffectPos );
		if ( tank->bullet.state == ProjFire )
		{
			DrawProjectileChroma( &(tank->bullet) );
			Sleep( 20 );
			DeleteRect( tank->bullet.rect );
		}
	}
}

void DrawTankOnce( Tank* tank )
{
	DrawSpriteNonChroma( (int)tank->pos.x, (int)tank->pos.y, &(tank->sprite) );
}

bool IsTankInMoveZone(Rect targetRect, Rect limitZone)
{
	return RectIsContainedBy( targetRect, GetScreenRect() ) && !RectIsOverlappingWith( targetRect, limitZone );
}

void DestroyTank( Tank* tank )
{
	DestroySurface( &(tank->sprite) );
	DestroySurface( &(tank->bulletSprite) );
	DestroySurface( &(tank->fireEffect) );
}