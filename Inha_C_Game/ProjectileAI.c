#include "ProjectileAI.h"

#include <Windows.h>
#include "Graphics.h"
#include <math.h>

void MakeProjectileAI(ProjectileAI* pProjAI, Surface* sprite, Color chroma, float damage, int sleepSpeed )
{
	MakeProjectile(&(pProjAI->model), sprite, chroma, damage, sleepSpeed );

	pProjAI->parpbolaMinHeight = 50;
	pProjAI->targetRange = 100;
}

void UpdateProjectileAI(ProjectileAI* pProjAI, Vec2 curProjPos, Vec2 targetPos, int aiOffset,
	Rect targetRect, Rect groundRect, Rect groundAIRect)
{
	ProjectileModel* pProjModel = &(pProjAI->model);

	switch (GetProjectileState( pProjModel ))
	{
	case ProjWait:
		// Initialize AI Projectile
		InitProjectileForParabola( pProjModel, curProjPos );
		CreateParabolaAI( pProjAI, targetPos, aiOffset );

		// Change State to Fire
		SetProjectileFire( pProjModel );
		break;

	case ProjFire:
		if (CheckProjectileScreen( pProjModel ))
		{
			// Update lastPos
			UpdateParabolaAI( pProjModel, pProjAI->fakeGravity );
			pProjModel->time += 0.1f;
			// Hit Target(Player)
			if (IsOverlapWithTarget( pProjModel, targetRect ))
			{
				SetProjectileHit( pProjModel );
			}
			// Hit Ground
			if (IsOverlapWithTarget( pProjModel, groundRect ) || IsOverlapWithTarget( pProjModel, groundAIRect ))
			{
				SetProjectileWait( pProjModel );
			}
		}
		// Out of screen
		else
		{
			SetProjectileWait( pProjModel );
		}
		break;
	}

}

void CreateParabolaAI(ProjectileAI* pProjAI, Vec2 playerPos, int difficultOffset)
{
	ProjectileModel* pProjModel = &(pProjAI->model);
	// Set for ParabolaAI

	// Get parabola vel.y
	pProjAI->maxTime = (float)(rand() % 2 + 3.0f);
	pProjAI->impactPos = MakeVec2(playerPos.x + rand() % (difficultOffset * 2) - difficultOffset + RectGetWidth(pProjModel->rect), playerPos.y);
	pProjAI->yDiffer = (int)(playerPos.y - pProjModel->startPos.y);
	pProjAI->prabolaMaxHeight = (float)(rand() % pProjAI->targetRange + pProjAI->parpbolaMinHeight);
	pProjAI->fakeGravity = (float)(pProjAI->prabolaMaxHeight * 2) / powf(pProjAI->maxTime, 2);
	pProjModel->vel.y = sqrtf(2 * pProjAI->fakeGravity * pProjAI->prabolaMaxHeight);

	// Get parabola vel.x
	const float a = pProjAI->fakeGravity;
	const float b = -2 * pProjModel->vel.y;
	const float c = (float)2 * pProjAI->yDiffer;
	pProjAI->parabolaEndTime = (-b + sqrtf(b * b - (4 * a * c))) / (2 * a);
	pProjModel->vel.x = (pProjAI->impactPos.x - pProjModel->startPos.x) / pProjAI->parabolaEndTime;
}

void UpdateParabolaAI( ProjectileModel* pProjModel, float fakeGravity)
{
	pProjModel->nextPos.x = pProjModel->startPos.x + (pProjModel->vel.x * pProjModel->time);
	pProjModel->nextPos.y = pProjModel->startPos.y - (float)((float)(pProjModel->vel.y * pProjModel->time) - (0.5 * fakeGravity * pow(pProjModel->time, 2)));
	pProjModel->nextRect = MakeRectBySize(pProjModel->nextPos, SurfaceGetWidth(pProjModel->sprite), SurfaceGetHeight(pProjModel->sprite));
	// Screen Check
	if (CheckProjectileScreen(pProjModel))
	{
		pProjModel->lastPos = pProjModel->pos;
		pProjModel->pos = pProjModel->nextPos;
		pProjModel->rect = pProjModel->nextRect;
	}
}

void DrawProjectileAI( ProjectileAI* pProjAI )
{
	ProjectileModel* pProjModel = &(pProjAI->model);
	if (pProjModel->state == ProjFire)
	{
		DrawProjectileChroma( pProjModel );
		Sleep( pProjModel->sleepSpeed );
		DeleteRect( pProjModel->rect );
	}
}