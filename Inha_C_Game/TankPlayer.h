#pragma once

#include "TankModel.h"
#include "Status.h"
#include "ProjectilePlayer.h"

typedef struct tankPlayer
{
	TankModel model;
	Status status;
	ProjectilePlayer bullet;
}TankPlayer;

void MakeTankPlayer( TankPlayer* pTankPlayer, TankType type, int pos_x, Vec2 groundPos, Rect limitZone );

void UpdatePlayerTank( TankPlayer* pTankPlayer, Vec2 dir, Rect targetRect, Rect groundRect );

ProjectileState GetPlayerBulletState( TankPlayer* pTankPlayer );

void DestroyTankPlayer( TankPlayer* pTankPlayer );
