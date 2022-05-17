#include "ProjectilePlayer.h"

#include <Windows.h>
#include "Graphics.h"
#include "MathSH.h"
#include <math.h>

void MakeProjectilePlayer(ProjectilePlayer* pProjPlayer, Surface* sprite, Color chroma, float damage, int sleepSpeed )
{
	MakeProjectile(&(pProjPlayer->model), sprite, chroma, damage, sleepSpeed );
}

void SetProjectilePlayerVars(ProjectilePlayer* pProjPlayer, int angle, int power)
{
	// Get Radian from angle, and make Velocity Vec2
	pProjPlayer->angle = angle;
	pProjPlayer->power = power;
	pProjPlayer->radian = angle * (PI / 180.0f);
	pProjPlayer->model.vel = MakeVec2(power * cosf(pProjPlayer->radian), -power * sinf(pProjPlayer->radian));
}

void UpdateProjectilePlayer(ProjectilePlayer* pProjPlayer, Vec2 curProjPos, int angle, int power,
	Rect targetTankRect, Rect groundRect, Rect groundAIRect )
{
	ProjectileModel* pProjModel = &(pProjPlayer->model);

	switch (GetProjectileState( pProjModel ))
	{
	case ProjWait:
		// Initialize Player Projectile
		InitProjectileForParabola( pProjModel, curProjPos );
		SetProjectilePlayerVars( pProjPlayer, angle, power );

		// Change State to Fire
		SetProjectileFire( pProjModel );
		break;

	case ProjFire:
		// Only in Screen
		if (CheckProjectileScreen( pProjModel ))
		{
			UpdateParabolaPlayer( pProjPlayer );
			pProjModel->time += 0.1f;

			// Hit Target(AI)
			if (IsOverlapWithTarget( pProjModel, targetTankRect ))
			{
				SetProjectileHit( pProjModel );
			}
			// Hit Ground
			if (IsOverlapWithTarget( pProjModel, groundRect ) || IsOverlapWithTarget( pProjModel, groundAIRect ))
			{
				SetProjectileWait( pProjModel );
			}
		}
		// Out of Screen
		else
		{
			SetProjectileWait( pProjModel );
		}
		break;
	}

}

void UpdateParabolaPlayer(ProjectilePlayer* pProjPlayer)
{
	ProjectileModel* pProjModel = &(pProjPlayer->model);
	pProjModel->nextPos.x = pProjModel->startPos.x + pProjPlayer->power * cosf(pProjPlayer->radian) * pProjModel->time;
	pProjModel->nextPos.y = pProjModel->startPos.y - (float)(pProjPlayer->power * sinf( pProjPlayer->radian ) * pProjModel->time
		- (0.5 * G * powf( pProjModel->time, 2 )));
	pProjModel->nextRect = MakeRectBySize(pProjModel->nextPos, SurfaceGetWidth(pProjModel->sprite), SurfaceGetHeight(pProjModel->sprite));

	if (CheckProjectileScreen(pProjModel))
	{
		pProjModel->lastPos = pProjModel->pos;
		pProjModel->pos = pProjModel->nextPos;
		pProjModel->rect = pProjModel->nextRect;
	}
}

void DrawProjectilePlayer( ProjectilePlayer* pProjPlayer )
{
	ProjectileModel* pProjModel = &(pProjPlayer->model);
	if (pProjModel->state == ProjFire)
	{
		DrawProjectileChroma( pProjModel );
		Sleep( pProjModel->sleepSpeed );
		DeleteRect( pProjModel->rect );
	}
}