#pragma once

#include <stdbool.h>
#include "Surface.h"

typedef struct projectile
{
	Vec2 pos;
	Vec2 vel;
	Vec2 startPos;
	Vec2 lastPos;
	Surface* sprite;
	Rect spriteRect;
	Color chroma;
	bool isFired;
	float time;
	float radian;
	int angle;
	int power;

	// ai feature
	Vec2 impactPos;
	float maxTime;
	int yDiffer;
	float height;
	float fakeGravity;
	float endTime;
	
}Projectile;

void MakeProjectile( Projectile* projectile, Vec2 startPos_in, int angle, int power, Surface* sprite, Color chroma );

void SetProjectileVel( Projectile* projectile, int angle, int power );

void StartFire( Projectile* projectile );

void UpdateProjectile( Projectile* projectile );

void ResetProjectile( Projectile* projectile );

bool IsInScreen( Projectile* projectile );

bool IsOverlapWithTarget( Projectile* projectile, Rect targetRect );

void MoveProjectile( Projectile* projectile );

void SetParabolaForUser( Projectile* projectile );

void DrawProjectile( Projectile* projectile );

void DrawProjectileClip( Rect clip, Projectile* projectile );

void DrawProjectileChroma(Projectile* projectile );

void DrawProjectileClipChroma(Rect clip, Projectile* projectile );

void DrawProjectileColor( Projectile* projectile, Color subColor );

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor );
