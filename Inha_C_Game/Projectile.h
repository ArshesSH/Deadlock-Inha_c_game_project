#pragma once

#include <stdbool.h>
#include "Surface.h"

typedef enum projectileState
{
	ProjWait,
	ProjFire,
	ProjCount
}ProjectileState;

typedef struct projectile
{
	Vec2 pos;
	Vec2 vel;
	Vec2 startPos;
	Vec2 lastPos;
	Vec2 nextPos;
	Surface* sprite;
	Rect rect;
	Rect nextRect;
	Color chroma;
	float time;
	float radian;
	int angle;
	int power;
	int damage;

	ProjectileState state;

	// ai feature
	Vec2 impactPos;
	float maxTime;
	int yDiffer;
	float height;
	float fakeGravity;
	float endTime;
	
}Projectile;

static const int aiParbolaMinHeight = 50;
static int aiParabolaRandomRange = 100;

void MakeProjectile( Projectile* projectile, Vec2 startPos_in, Surface* sprite, Color chroma );

void SetProjectileAI( Projectile* projectile, Vec2 playerPos, Vec2 aiPos, int difficultOffset );

void SetProjectilePlayer( Projectile* projectile, int angle, int power );

void SetProjectile( Projectile* projectile, Vec2 pos );

void SetProjectileStateFire( Projectile* projectile );

void UpdateProjectilePlayer( Projectile* projectile );

void UpdatePrjectileAI( Projectile* projectile );

void EndProjectile( Projectile* projectile, Vec2 pos );

bool IsNextProjectileInScreen( Projectile* projectile );

bool IsOverlapWithTarget( Projectile* projectile, Rect targetRect );

void SetParabolaForUser( Projectile* projectile );

void SetParabolaForAI( Projectile* projectile );

void DrawProjectile( Projectile* projectile );

void DrawProjectileClip( Rect clip, Projectile* projectile );

void DrawProjectileChroma(Projectile* projectile );

void DrawProjectileClipChroma(Rect clip, Projectile* projectile );

void DrawProjectileColor( Projectile* projectile, Color subColor );

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor );
