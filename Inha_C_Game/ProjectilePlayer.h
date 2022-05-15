#pragma once

#include "ProjectileModel.h"

typedef struct projectilePlayer
{
	ProjectileModel model;

	float radian;
	int angle;
	int power;
}ProjectilePlayer;

void MakeProjectilePlayer( ProjectilePlayer* pProjPlayer, Surface* sprite, Color chroma, float damage );

void SetProjectilePlayerVars( ProjectilePlayer* pProjPlayer, int angle, int power );

void UpdateProjectilePlayer( ProjectilePlayer* pProjPlayer, Vec2 curProjPos, int angle, int power, Rect targetTankRect, Rect groundRect );

void UpdateParabolaPlayer( ProjectilePlayer* pProjPlayer );

void DrawProjectilePlayer( ProjectilePlayer* pProjPlayer );
