#pragma once

#include <stdbool.h>
#include "Surface.h"
#include "Projectile.h"

typedef enum tankType
{
	LightTank,
	MiddleTank,
	HeavyTank,
	MRL,
	LightTankAI,
	MiddleTankAI,
	HeavyTankAI,
	MRLAI
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
	Surface bulletSprite;
	Projectile bullet;
	Vec2 gunPos;
	Surface sprite;
	Vec2 pos;
	Rect rect;
	Rect lastRect;
	int speed;
	TankState state;
}Tank;

static int aiCount;
static int aiMaxCount;
static int aiDir;

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos );

void UpdateTankPlayer( Tank* tank, Vec2 dir );

void UpdateTankAI( Tank* tank, Rect ground, Vec2 userPos, int aiDiffOffset );

void MoveTank( Tank* tank, Vec2 dir );

void SetTankAIStateMove( Tank* tank );

void SetTankPlayerStateMove( Tank* tank );

void MoveTankAI( Tank* tank );

void SetTankAIStateFire( Tank* tank );

bool IsTankOverlapWith( Tank* tank, Rect target );

void DrawTank( Tank* tank );

void DrawTankOnce( Tank* tank );
