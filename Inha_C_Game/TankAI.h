#pragma once
#include "TankModel.h"
#include "Status.h"
#include "ProjectileAI.h"

typedef struct tankAI
{
	TankModel model;
	Status status;
	ProjectileAI bullet;

	int aiOffset;
	int aiCount;
	int aiMaxCount;
	int aiDir;
}TankAI;


void MakeTankAI( TankAI* pTankAI, TankType type, int pos_x, Vec2 groundPos, Rect limitZone, int aiDifficult );

void UpdateTankAI( TankAI* pTankAI, Vec2 targetPos, Rect targetRect, Rect groundRect );

void SetTankAIMoveCount( TankAI* pTankAI );

ProjectileState GetAIBulletState( TankAI* pTankAI );

void DestroyTankAI( TankAI* pTankAI );
