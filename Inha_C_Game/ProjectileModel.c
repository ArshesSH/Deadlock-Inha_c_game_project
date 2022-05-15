#include "ProjectileModel.h"

#include "Graphics.h"
#include "MathSH.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void MakeProjectile(ProjectileModel* pProj, Surface* sprite, Color chroma, float damage)
{
	// Set Image of projectile
	pProj->sprite = sprite;
	pProj->rect = MakeRectBySize(pProj->pos, sprite->width, sprite->height );
	pProj->nextRect = pProj->rect;

	// Set Image Chroma
	pProj->chroma = chroma;

	// Set Time
	pProj->time = 0.0f;
	pProj->damage = damage;

	pProj->state = ProjWait;

}

void InitProjectileForParabola(ProjectileModel* pProj, Vec2 curStartPos )
{
	pProj->time = 0;
	pProj->pos = curStartPos;
	pProj->rect = MakeRectBySize( curStartPos, SurfaceGetWidth( pProj->sprite ), SurfaceGetHeight( pProj->sprite ) );
	pProj->nextRect = pProj->rect;
	pProj->lastPos = curStartPos;
	pProj->startPos = curStartPos;
	PlaySound( TEXT( "src/sounds/fire.wav" ), NULL, SND_ASYNC );
}

// Check is projectile in screen except top of screen
bool CheckProjectileScreen(ProjectileModel* pProj )
{
	const Rect screenRect = GetScreenRect();
	return pProj->nextRect.left >= screenRect.left && pProj->nextRect.right <= screenRect.right
		&& pProj->nextRect.bottom <= screenRect.bottom;
}

bool IsOverlapWithTarget(ProjectileModel* pProj, Rect targetRect )
{
	return RectIsOverlappingWith(pProj->rect, targetRect );
}

void SetProjectileWait( ProjectileModel* pProj )
{
	pProj->state = ProjWait;
}

void SetProjectileFire(ProjectileModel* pProj)
{
	pProj->state = ProjFire;
}

void SetProjectileHit(ProjectileModel* pProj)
{
	pProj->state = ProjHit;
}

void DrawProjectile(ProjectileModel* pProj)
{
	DrawProjectileClip( GetScreenRect(), pProj);
}

void DrawProjectileClip( Rect clip, ProjectileModel* pProj)
{
	DrawSpriteClipNonChroma( (int)pProj->pos.x, (int)pProj->pos.y, SurfaceGetRect( (pProj->sprite) ), clip, pProj->sprite );
}


void DrawProjectileChroma(ProjectileModel* pProj)
{
	DrawProjectileClipChroma( GetScreenRect(), pProj);
}

void DrawProjectileClipChroma( Rect clip, ProjectileModel* pProj)
{
	DrawSpriteClipChroma( (int)pProj->pos.x, (int)pProj->pos.y, SurfaceGetRect( (pProj->sprite) ), clip, pProj->sprite, pProj->chroma );
}


void DrawProjectileColor(ProjectileModel* pProj, Color subColor )
{
	DrawProjectileClipColor( GetScreenRect(), pProj, subColor );
}

void DrawProjectileClipColor( Rect clip, ProjectileModel* pProj, Color subColor )
{
	DrawSpriteClipSubstitute( (int)pProj->pos.x, (int)pProj->pos.y, SurfaceGetRect((pProj->sprite)), clip, pProj->sprite, pProj->chroma, subColor );
}

ProjectileState GetProjectileState(ProjectileModel* pProj)
{
	return pProj->state;
}


/*
// Old Function
void ChangeProjectilePosPlayer( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->rect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForUser( projectile );
	projectile->time += 0.1f;
}

// Old Function
void ChangeProjectilePosAI( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->rect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForAI( projectile );
	projectile->time += 0.1f;
}

// Update Function
void UpdateProjectile(Projectile* pProj, Vec2 startPos)
{
	if (pProj->state == ProjWait)
	{
		SetProjectile(pProj, tank->gunPos);
		SetProjectilePlayer(&(tank->bullet), angle, power);
		SetProjectileStateFire(&(tank->bullet));
		StartEffect(&(tank->fireEffect));
	}
	else if (pProj->state == ProjFire)
	{
		// Update lastPos
		pProj->lastPos = pProj->pos;
		pProj->rect = MakeRectBySize(pProj->pos, pProj->sprite->width, pProj->sprite->height);

		if (pProj->type == ProjectilePlayer)
		{
			SetParabolaForUser(pProj);
		}
		else if (pProj->type == ProjectileAI)
		{
			SetParabolaForAI(pProj);
		}
		pProj->time += 0.1f;
	}
	else if (pProj->state == ProjHit)
	{

	}
}

*/
