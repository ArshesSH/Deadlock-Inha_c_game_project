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
	TankFire,
	TankDamaged,
	TankDestroyed
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
	float bulletDamage;
	int tankSpeed;
	float tankMaxHealth;
	int tankMinAngle;
	int tankMaxAngle;
	int tankMinPower;
	int tankMaxPower;
	int gunPosYOffset;
	int firePosXOffset;
	float fireEffectCenterY;
}TankModel;

void MakeTankModel( TankModel* pTank, TankType type, int pos_x, Vec2 groundPos, Rect limitZone );

void MoveTank( TankModel* pTank, Vec2 dir, Rect limitZone );

void SetTankStateWait( TankModel* pTank );

void SetTankStateMove( TankModel* pTank );

void SetTankStateFire( TankModel* pTank );

void SetTankStateDamaged( TankModel* pTank );

void SetTankStateDestroyed( TankModel* pTank );

bool IsTankOverlapWith( TankModel* pTank, Rect target );

void DrawTank( TankModel* pTank );

void DrawTankOnce( TankModel* pTank );

bool IsTankInMoveZone( TankModel* pTank );

void DestroyTank( TankModel* pTank );