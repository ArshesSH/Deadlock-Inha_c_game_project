#pragma once

#include "ProjectileModel.h"

typedef struct projectileAI
{
	ProjectileModel model;

	Vec2 impactPos;
	float maxTime;
	int yDiffer;
	float prabolaMaxHeight;
	float fakeGravity;
	float parabolaEndTime;
	int parpbolaMinHeight;
	int targetRange;
}ProjectileAI;

void MakeProjectileAI( ProjectileAI* pProjAI, Surface* sprite, Color chroma, float damage, int sleepSpeed );

void UpdateProjectileAI( ProjectileAI* pProjAI, Vec2 curProjPos, Vec2 targetPos, int aiOffset,
	Rect targetRect, Rect groundRect, Rect groundAIRect );

void CreateParabolaAI( ProjectileAI* pProjAI, Vec2 playerPos, int difficultOffset );

void UpdateParabolaAI( ProjectileModel* pProjModel, float fakeGravity );

void DrawProjectileAI( ProjectileAI* pProjAI );
