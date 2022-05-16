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
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA, 1.0f );
		pTank->tankSpeed = 10;
		pTank->tankMaxHealth = 100;
		pTank->tankMaxAngle = 20;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 100;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 20;
		pTank->gunPosYOffset = 5;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		pTank->bulletSpeed = 20;
		break;

	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet1Flip.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, 1.0f );
		pTank->tankSpeed = 10;
		pTank->tankMaxHealth = 100;
		pTank->bulletDamage = 20;
		pTank->gunPos.x = -(float)pTank->bulletSprite.width;
		pTank->gunPosYOffset = 5;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		pTank->bulletSpeed = 10;
		break;

	case MediumTank:
		MakeSurface( "src/images/tank/player/MediumTankGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA, 1.0f );
		pTank->tankSpeed = 5;
		pTank->tankMaxHealth = 150;
		pTank->tankMaxAngle = 22;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 120;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 30;
		pTank->gunPosYOffset = 5;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		pTank->bulletSpeed = 20;
		break;

	case MediumTankAI:
		MakeSurface( "src/images/tank/ai/MediumTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, 1.0f );
		pTank->tankSpeed = 5;
		pTank->tankMaxHealth = 150;
		pTank->bulletDamage = 30;
		pTank->gunPos.x = -(float)pTank->bulletSprite.width;
		pTank->gunPosYOffset = 5;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		pTank->bulletSpeed = 10;
		break;

	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1.bmp", MAGENTA,  1.0f );
		pTank->tankSpeed = 1;
		pTank->tankMaxHealth = 200;
		pTank->tankMaxAngle = 35;
		pTank->tankMinAngle = 10;
		pTank->tankMaxPower = 120;
		pTank->tankMinPower = 40;
		pTank->bulletDamage = 40;
		pTank->gunPosYOffset = -2;
		pTank->gunPos.x = (float)pTank->sprite.width;
		pTank->firePosXOffset = 0;
		pTank->bulletSpeed = 20;
		break;

	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bullet.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire1Flip.bmp", MAGENTA, 1.0f );
		pTank->tankSpeed = 1;
		pTank->tankMaxHealth = 200;
		pTank->bulletDamage = 40;
		pTank->gunPos.x = -(float)pTank->bulletSprite.width;
		pTank->gunPosYOffset = -2;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		pTank->bulletSpeed = 10;
		break;

	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bulletFire.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire2.bmp", MAGENTA,  1.0f );
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
		pTank->bulletSpeed = 4;
		break;

	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip30.bmp", &(pTank->sprite) );
		MakeSurface( "src/images/bulletFireFlip.bmp", &(pTank->bulletSprite) );
		MakeEffect( &(pTank->fireEffect), "src/images/fire2Flip.bmp", MAGENTA,  1.0f );
		pTank->tankSpeed = 3;
		pTank->tankMaxHealth = 80;
		pTank->bulletDamage = 50;
		pTank->gunPos.x = -(float)pTank->bulletSprite.width;
		pTank->gunPosYOffset = -10;
		pTank->firePosXOffset = -pTank->fireEffect.sprite.width;
		pTank->bulletSpeed = 2;
		break;
	}

	// Tank Position
	pTank->pos.x = (float)pos_x;
	pTank->pos.y = groundPos.y - pTank->sprite.height;
	
	// Tank Gun Position
	pTank->gunPos.x += pTank->pos.x;
	pTank->gunPos.y = pTank->pos.y + pTank->gunPosYOffset;
	pTank->fireEffectCenterY = (pTank->fireEffect.sprite.height / 2) + pTank->pos.y + pTank->gunPosYOffset;

	// Tank Damage Effect
	MakeEffect( &(pTank->hitEffect), "src/images/fire3.bmp", MAGENTA,  0.5f );
	
	pTank->limitZone = limitZone;

	pTank->rect = MakeRectBySize( pTank->pos, pTank->sprite.width, pTank->sprite.height );
	pTank->lastRect = pTank->rect;
	pTank->nextRect = pTank->rect;
	pTank->hitPos.y = pTank->pos.y - pTank->hitEffect.sprite.height;

	pTank->state = TankWait;
}

void MoveTank( TankModel* pTank, Vec2 dir, Rect limitZone )
{
	const Vec2 vel = Vec2Mul( dir, (float)pTank->tankSpeed );
	const Vec2 nextPos = Vec2Add( (pTank->pos), vel );
	pTank->nextRect = MakeRectBySize( nextPos, pTank->sprite.width, pTank->sprite.height );
	pTank->lastRect = pTank->rect;

	// Screen Check
	if ( IsTankInMoveZone( pTank->nextRect, pTank->limitZone ) )
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

bool IsTankOverlapWith(TankModel* pTank, Rect target)
{
	return RectIsOverlappingWith( pTank->rect, target );
}

void DrawTank( TankModel* pTank )
{
	switch (pTank->state)
	{
	case TankWait:
		// Delete last Sprite and Draw at New Pos
		DeleteRect( pTank->lastRect );
		DrawTankSprite( pTank );
		pTank->state = TankDrawAndWait;
		break;

	case TankMove:
		// Delete last Sprite and Draw at New Pos
		DeleteRect( pTank->lastRect );
		DrawSpriteNonChroma( (int)pTank->pos.x, (int)pTank->pos.y, &(pTank->sprite) );
		break;

	case TankFire:
		// Draw Effects on fireEffectPos
		DrawEffect( &(pTank->fireEffect), MakeVec2( pTank->gunPos.x + pTank->firePosXOffset, pTank->fireEffectCenterY ) );
		break;
	}

	DrawEffect( &(pTank->hitEffect), pTank->hitPos );
}

void DrawTankSprite( TankModel* pTank )
{
	DrawSpriteNonChroma( (int)pTank->pos.x, (int)pTank->pos.y, &(pTank->sprite) );
}

bool IsTankInMoveZone( Rect nextRect, Rect limitZone )
{
	return RectIsContainedBy(nextRect, GetScreenRect() ) && !RectIsOverlappingWith( nextRect, limitZone );
}

void DestroyTank( TankModel* pTank )
{
	DestroySurface( &(pTank->sprite) );
	DestroySurface( &(pTank->bulletSprite) );
	DestroyEffect( &(pTank->fireEffect) );
	DestroyEffect( &(pTank->hitEffect) );
}