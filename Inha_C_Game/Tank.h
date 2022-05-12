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
	TankMove,
	TankFire,
	TankCount
}TankState;

typedef struct tank
{
	TankType type;
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

void SetTankAIToMove( Tank* tank );

void UpdateTankAI( Tank* tank );

void MoveTank( Tank* tank, Vec2 dir );

void MoveTankAI( Tank* tank );

bool IsTankOverlapWith( Tank* tank, Rect target );

void DrawTank( Tank* tank );
