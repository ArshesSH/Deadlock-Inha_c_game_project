#pragma once

#include "Surface.h"
#include "Projectile.h"

typedef enum tankType
{
	LightTank,
	MiddleTank,
	MRL,
	LightTankAI,
	MiddleTankAI,
	MRLAI
}TankType;

typedef struct tank
{
	TankType type;
	Vec2 pos;
	int speed;
}Tank;