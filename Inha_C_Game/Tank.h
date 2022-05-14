#pragma once

#include <stdbool.h>
#include "Surface.h"
#include "Projectile.h"
#include "Effect.h"

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
	TankCount
}TankState;

typedef struct tank
{
	TankType type;
	TankState state;
	Surface sprite;
	Surface bulletSprite;
	Vec2 gunPos;
	Vec2 pos;
	Vec2 hitPos;
	Rect rect;
	Rect lastRect;
	Rect nextRect;
	Projectile bullet;
	Effect fireEffect;
	Effect hitEffect;
	int tankSpeed;
	int tankMaxHealth;
	int tankMinAngle;
	int tankMaxAngle;
	int tankMinPower;
	int tankMaxPower;
	int gunPosYOffset;
	int firePosXOffset;
	float fireEffectCenterY;
}Tank;

static int aiCount;
static int aiMaxCount;
static int aiDir;

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos );

void UpdateTankPlayer( Tank* tank, Rect targetTankRect, Rect ground, Vec2 dir, int angle, int power, Rect limitZone );

void UpdateTankAI( Tank* tank, Rect targetTankRect, Rect ground, Vec2 userPos, int aiDiffOffset, Rect limitZone );

void MoveTank( Tank* tank, Vec2 dir, Rect limitZone );

void SetTankAIStateMove( Tank* tank );

void SetTankPlayerStateMove( Tank* tank );

void MoveTankAI( Tank* tank, Rect limitZone );

void SetTankStateFire( Tank* tank );

bool IsTankOverlapWith( Tank* tank, Rect target );

void DrawTank( Tank* tank );

void DrawTankOnce( Tank* tank );

bool IsTankInMoveZone( Rect targetRect, Rect limitZone );

void DestroyTank( Tank* tank );
