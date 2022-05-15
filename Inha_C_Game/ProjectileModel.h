#pragma once

#include <stdbool.h>
#include "Surface.h"

typedef enum projectileState
{
	ProjWait,
	ProjFire,
	ProjHit
}ProjectileState;

typedef struct projectileModel
{
	// States
	ProjectileState state;

	// Vector for Parabola
	Vec2 pos;
	Vec2 vel;

	// Sprite and Rect
	Surface* sprite;
	Rect rect;
	Rect nextRect;
	Color chroma;

	// Status of Projectile
	Vec2 startPos;
	Vec2 lastPos;
	Vec2 nextPos;
	float time;
	float damage;
	
}ProjectileModel;

void MakeProjectile( ProjectileModel* pProj, Surface* sprite, Color chroma, float damage );

void InitProjectileForParabola( ProjectileModel* pProj, Vec2 curStartPos );

bool CheckProjectileScreen( ProjectileModel* pProj );

bool IsOverlapWithTarget( ProjectileModel* pProj, Rect targetRect );

void SetProjectileWait( ProjectileModel* pProj );

void SetProjectileFire( ProjectileModel* pProj );

void SetProjectileHit( ProjectileModel* pProj );

void DrawProjectile( ProjectileModel* pProj );

void DrawProjectileClip( Rect clip, ProjectileModel* pProj );

void DrawProjectileChroma( ProjectileModel* pProj );

void DrawProjectileClipChroma( Rect clip, ProjectileModel* pProj );

void DrawProjectileColor( ProjectileModel* pProj, Color subColor );

void DrawProjectileClipColor( Rect clip, ProjectileModel* pProj, Color subColor );

ProjectileState GetProjectileState( ProjectileModel* pProj );
