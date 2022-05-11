#include "Projectile.h"

#include "Graphics.h"
#include "MathSH.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void MakeProjectile(Projectile* projectile, Vec2 startPos_in, Surface* sprite, Color chroma)
{
	// Set Projectile Start Position
	projectile->startPos = startPos_in;
	projectile->pos = startPos_in;
	projectile->lastPos = startPos_in;

	// Set Image of projectile
	projectile->sprite = sprite;
	projectile->spriteRect = MakeRectBySize( projectile->pos, sprite->width, sprite->height );

	// Set Image Chroma
	projectile->chroma = chroma;
	projectile->isFired = false;

	// Set Time
	projectile->time = 0.0f;
}

void SetProjectileVelAI( Projectile* projectile, Vec2 playerPos, Vec2 aiPos, int difficultOffset )
{
	// Set for ParabolaAI

	projectile->maxTime = 2.0f;
	projectile->impactPos = MakeVec2( playerPos.x + rand() % (difficultOffset * 2) - difficultOffset + RectGetWidth(projectile->spriteRect), playerPos.y );
	projectile->yDiffer = (int)(playerPos.y - aiPos.y);
	projectile->height = (float)(rand() % 200 + 50);
	projectile->fakeGravity = (float)(projectile->height * 2) / (projectile->maxTime * projectile->maxTime);
	projectile->vel.y = sqrtf( 2 * projectile->fakeGravity * projectile->height );

	const float a = projectile->fakeGravity;
	const float b = -2 * projectile->vel.y;
	const float c = (float)2 * projectile->yDiffer;
	projectile->endTime = (-b + sqrtf( b * b - (4 * a * c) )) / (2 * a);
	projectile->vel.x = (projectile->impactPos.x - aiPos.x) / projectile->endTime;
}

void SetProjectileVel( Projectile* projectile, int angle, int power)
{
	// Get Radian from angle, and make Velocity Vec2
	projectile->radian = angle * (PI / 180.0f);
	projectile->vel = MakeVec2( power * cosf( projectile->radian ), -power * sinf( projectile->radian ) );
}

void StartProjectileFire(Projectile* projectile)
{
	projectile->isFired = true;
	projectile->lastPos = projectile->startPos;
}

void UpdateProjectile( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->spriteRect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForUser( projectile );
	projectile->time += 0.1f;
}

void UpdatePrjectileAI( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->spriteRect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForAI( projectile );
	projectile->time += 0.1f;
}


void ResetProjectile( Projectile* projectile )
{
	projectile->pos = projectile->startPos;
	projectile->spriteRect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	projectile->time = 0;
	projectile->isFired = false;
}

bool IsInScreen( Projectile* projectile )
{
	const Rect screenRect = GetScreenRect();
	
	// Check except Screen Top
	return projectile->spriteRect.left >= screenRect.left && projectile->spriteRect.right <= screenRect.right
		&& projectile->spriteRect.bottom <= screenRect.bottom;
}

bool IsOverlapWithTarget( Projectile* projectile, Rect targetRect )
{
	return RectIsOverlappingWith( SurfaceGetRect( projectile->sprite ), targetRect );
}

void MoveProjectile( Projectile* projectile )
{
	projectile->vel.y += G;
	projectile->pos.x += projectile->vel.x;
	projectile->pos.y = projectile->pos.y + projectile->vel.y;
}

void SetParabolaForUser( Projectile* projectile )
{
	projectile->pos.x = projectile->startPos.x + projectile->power * cosf( projectile->radian ) * projectile->time;
	projectile->pos.y = projectile->startPos.y - (float)(projectile->power * sinf( projectile->radian ) * projectile->time
		- (0.5 * G * projectile->time * projectile->time));
}

void SetParabolaForAI( Projectile* projectile )
{
	projectile->pos.x = projectile->startPos.x + (projectile->vel.x * projectile->time);
	projectile->pos.y = projectile->startPos.y - ((float)(projectile->vel.y * projectile->time) - (0.5 * projectile->fakeGravity * pow( projectile->time, 2 )));
}

bool IsProjectFired( Projectile* projectile )
{
	return projectile->isFired;
}

void DrawProjectile( Projectile* projectile )
{
	DrawProjectileClip( GetScreenRect(), projectile );
}

void DrawProjectileClip( Rect clip, Projectile* projectile )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipNonChroma( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite );
}


void DrawProjectileChroma(  Projectile* projectile )
{
	DrawProjectileClipChroma( GetScreenRect(), projectile );
}

void DrawProjectileClipChroma( Rect clip, Projectile* projectile )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipChroma( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite, projectile->chroma );
}


void DrawProjectileColor( Projectile* projectile, Color subColor )
{
	DrawProjectileClipColor( GetScreenRect(), projectile, subColor );
}

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipSubstitute( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect((projectile->sprite)), clip, projectile->sprite, projectile->chroma, subColor );
}