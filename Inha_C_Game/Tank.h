#pragma once

#include <stdbool.h>
#include "Surface.h"
#include "Projectile.h"

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
	Rect rect;
	Rect lastRect;
	Projectile bullet;
	int tankSpeed;
	int tankMaxHealth;
	int tankMinAngle;
	int tankMaxAngle;
	int tankMinPower;
	int tankMaxPower;
}Tank;

static int aiCount;
static int aiMaxCount;
static int aiDir;

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos );

void UpdateTankPlayer( Tank* tank, Rect ground, Vec2 dir, int angle, int power );

void UpdateTankAI( Tank* tank, Rect ground, Vec2 userPos, int aiDiffOffset );

void MoveTank( Tank* tank, Vec2 dir );

void SetTankAIStateMove( Tank* tank );

void SetTankPlayerStateMove( Tank* tank );

void MoveTankAI( Tank* tank );

void SetTankStateFire( Tank* tank );

bool IsTankOverlapWith( Tank* tank, Rect target );

void DrawTank( Tank* tank );

void DrawTankOnce( Tank* tank );
