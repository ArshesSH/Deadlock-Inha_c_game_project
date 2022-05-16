#pragma once

#include <stdbool.h>
#include "Surface.h"
#include "Effect.h"
#include "ProjectileModel.h"

// Type of Tanks
typedef enum tankType
{
	// For Check Player Type
	LightTank,
	MediumTank,
	HeavyTank,
	MRL,

	// For Check AI Type
	LightTankAI,
	MediumTankAI,
	HeavyTankAI,
	MRLAI,

	// For Check Player Selection
	SelectLightTank,
	SelectMediumTank,
	SelectHeavyTank,
	SelectMRL
}TankType;

typedef enum tankState
{
	TankWait,
	TankDrawAndWait,
	TankMove,
	TankFire
}TankState;

typedef struct tankModel
{
	// Tank State
	TankType type;
	TankState state;

	// Projectile Feature
	Surface bulletSprite;
	Surface sprite;

	Vec2 gunPos;
	Vec2 pos;
	Vec2 hitPos;
	Rect limitZone;
	Rect rect;
	Rect lastRect;
	Rect nextRect;

	Effect fireEffect;
	Effect hitEffect;

	float fireEffectCenterY;
	float bulletDamage;
	float tankMaxHealth;
	int tankSpeed;
	int tankMinAngle;
	int tankMaxAngle;
	int tankMinPower;
	int tankMaxPower;
	int gunPosYOffset;
	int firePosXOffset;
	int bulletSpeed;
}TankModel;

void MakeTankModel( TankModel* pTank, TankType type, int pos_x, Vec2 groundPos, Rect limitZone );

void MoveTank( TankModel* pTank, Vec2 dir, Rect limitZone );

void SetTankStateWait( TankModel* pTank );

void SetTankStateMove( TankModel* pTank );

void SetTankStateFire( TankModel* pTank );

bool IsTankOverlapWith( TankModel* pTank, Rect target );

void DrawTank( TankModel* pTank );

void DrawTankSprite( TankModel* pTank );

bool IsTankInMoveZone( Rect nextRect, Rect limitZone );

void DestroyTank( TankModel* pTank );

void SetCaterpillars( TankModel* pTank );
