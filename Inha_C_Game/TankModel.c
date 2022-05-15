#include "TankModel.h"

#include "Graphics.h"
#include <stdlib.h>
#include <Windows.h>

void MakeTankModel( TankModel* pTank, TankType type, int pos_x, Vec2 groundPos, Rect limitZone )
{
	pTank->type = type;
	switch ( type )
	{
	case LightTank:
		MakeSurface( "src/images/tank/player/LightTankGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet1.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 10;
		pTank->tankMaxHealth = 100;
		pTank->tankMaxAngle = 20;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 100;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 10;
		pTank->gunPosYOffset = 5;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		break;

	case MediumTank:
		MakeSurface( "src/images/tank/player/MediumTankGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 5;
		pTank->tankMaxHealth = 150;
		pTank->tankMaxAngle = 22;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 120;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 20;
		pTank->gunPosYOffset = 5;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		break;

	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 1;
		pTank->tankMaxHealth = 200;
		pTank->tankMaxAngle = 35;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 120;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 30;
		pTank->gunPosYOffset = -2;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		break;

	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bulletFire.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire2.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 3;
		pTank->tankMaxHealth = 80;
		pTank->tankMaxAngle = 75;
		pTank->tankMinAngle = 50;
		pTank->tankMaxPower = 150;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 50;
		pTank->gunPosYOffset = -10;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		break;

	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet1.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 10;
		pTank->tankMaxHealth = 100;
		pTank->bulletDamage = 10;
		pTank->gunPos.x = 0.0f;
		pTank->gunPosYOffset = 5;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		break;

	case MediumTankAI:
		MakeSurface( "src/images/tank/ai/MediumTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 5;
		pTank->tankMaxHealth = 150;
		pTank->bulletDamage = 20;
		pTank->gunPos.x = 0.0f;
		pTank->gunPosYOffset = 5;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		break;

	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 1;
		pTank->tankMaxHealth = 200;
		pTank->bulletDamage = 30;
		pTank->gunPos.x = 0.0f;
		pTank->gunPosYOffset = -2;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		break;

	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bulletFire.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire2Flip.bmp", MAGENTA, "src/coin.wav", 1.0f );
		pTank->tankSpeed = 3;
		pTank->tankMaxHealth = 80;
		pTank->bulletDamage = 50;
		pTank->gunPos.x = 0.0f;
		pTank->gunPosYOffset = 0;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		break;
	}

	pTank->pos.x = (float)pos_x;
	pTank->pos.y = groundPos.y - pTank->sprite.height;
	
	pTank->gunPos.x += pTank->pos.x;
	pTank->gunPos.y = pTank->pos.y + pTank->gunPosYOffset;

	//MakeProjectile( &(pTank->bullet), pTank->gunPos, &(pTank->bulletSprite), MAGENTA );
	//MakeEffect( &(pTank->hitEffect), "src/images/fire3.bmp", MAGENTA, "src/coin.wav", 1.0f );

	pTank->limitZone = limitZone;

	pTank->rect = MakeRectBySize( pTank->pos, pTank->sprite.width, pTank->sprite.height );
	pTank->lastRect = pTank->rect;
	pTank->nextRect = pTank->rect;
	pTank->fireEffectCenterY = (pTank->fireEffect.sprite.height / 2) + pTank->pos.y + pTank->gunPosYOffset;

	pTank->state = TankWait;
}

void MoveTank( TankModel* pTank, Vec2 dir, Rect limitZone )
{
	const Vec2 vel = Vec2Mul( dir, (float)pTank->tankSpeed );
	const Vec2 nextPos = Vec2Add( (pTank->pos), vel );
	pTank->nextRect = MakeRectBySize( nextPos, pTank->sprite.width, pTank->sprite.height );
	pTank->lastRect = pTank->rect;

	// Screen Check
	if ( IsTankInMoveZone( pTank ) )
	{
		pTank->pos = nextPos;
		pTank->rect = pTank->nextRect;
		Vec2AddEqual( &(pTank->gunPos), vel );
	}
}

void SetTankStateWait( TankModel* pTank )
{
	pTank->state = TankWait;
}

void SetTankStateMove( TankModel* pTank )
{
	pTank->state = TankMove;
}

void SetTankStateFire( TankModel* pTank )
{
	pTank->state = TankFire;
}

void SetTankStateDamaged( TankModel* pTank )
{
	pTank->state = TankDamaged;
}

void SetTankStateDestroyed( TankModel* pTank )
{
	pTank->state = TankDestroyed;
}


bool IsTankOverlapWith(TankModel* pTank, Rect target)
{
	return RectIsOverlappingWith( pTank->rect, target );
}

void DrawTank( TankModel* pTank )
{
	if ( pTank->state == TankWait )
	{
		DeleteRect( pTank->lastRect );
		DrawTankOnce( pTank );
		pTank->state = TankDrawAndWait;
	}
	else if ( pTank->state == TankMove )
	{
		DeleteRect( pTank->lastRect );
		DrawSpriteNonChroma( (int)pTank->pos.x, (int)pTank->pos.y, &(pTank->sprite) );
	}
	else if ( pTank->state == TankFire )
	{

		const Vec2 fireEffectPos = { pTank->gunPos.x + pTank->firePosXOffset, pTank->fireEffectCenterY };
		DrawEffect( &(pTank->fireEffect), fireEffectPos );
	}
}

void DrawTankOnce( TankModel* pTank )
{
	DrawSpriteNonChroma( (int)pTank->pos.x, (int)pTank->pos.y, &(pTank->sprite) );
}

bool IsTankInMoveZone( TankModel* pTank )
{
	return RectIsContainedBy( pTank->rect, GetScreenRect() ) && !RectIsOverlappingWith( pTank->rect, pTank->limitZone );
}



void DestroyTank( TankModel* pTank )
{
	DestroySurface( &(pTank->sprite) );
	DestroySurface( &(pTank->bulletSprite) );
	//DestroySurface( &(pTank->fireEffect) );
}

/*
* Old Functions
* 
* 
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
	void MoveTankAI( TankModel* pTank, Rect limitZone )
	{
		MoveTank( tank, MakeVec2( (float)aiDir, 0.0f ), limitZone );
	}
	bool IsTankInMoveZone(Rect targetRect, Rect limitZone)
{
	return RectIsContainedBy( targetRect, GetScreenRect() ) && !RectIsOverlappingWith( targetRect, limitZone );
}
* 
*/