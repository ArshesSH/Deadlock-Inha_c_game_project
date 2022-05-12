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
	projectile->rect = MakeRectBySize( projectile->pos, sprite->width, sprite->height );
	projectile->nextRect = projectile->rect;

	// Set Image Chroma
	projectile->chroma = chroma;

	// Set Time
	projectile->time = 0.0f;

	projectile->state = ProjWait;
}

void UpdateProjectilePlayer( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->rect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForUser( projectile );
	projectile->time += 0.1f;
}

void UpdatePrjectileAI( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->rect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForAI( projectile );
	projectile->time += 0.1f;
}


void SetProjectileStateFire( Projectile* projectile )
{
	projectile->state = ProjFire;
}

void SetProjectileAI( Projectile* projectile, Vec2 playerPos, Vec2 aiPos, int difficultOffset )
{
	// Set for ParabolaAI
	projectile->maxTime = (float)(rand() % 2 + 3.0f);
	projectile->impactPos = MakeVec2( playerPos.x + rand() % (difficultOffset * 2) - difficultOffset + RectGetWidth(projectile->rect ), playerPos.y );
	projectile->yDiffer = (int)(playerPos.y - aiPos.y);
	projectile->height = (float)(rand() % aiParabolaRandomRange + aiParbolaMinHeight);
	projectile->fakeGravity = (float)(projectile->height * 2) / (projectile->maxTime * projectile->maxTime);
	projectile->vel.y = sqrtf( 2 * projectile->fakeGravity * projectile->height );

	const float a = projectile->fakeGravity;
	const float b = -2 * projectile->vel.y;
	const float c = (float)2 * projectile->yDiffer;
	projectile->endTime = (-b + sqrtf( b * b - (4 * a * c) )) / (2 * a);
	projectile->vel.x = (projectile->impactPos.x - aiPos.x) / projectile->endTime;
}

void SetProjectilePlayer( Projectile* projectile, int angle, int power)
{
	// Get Radian from angle, and make Velocity Vec2
	projectile->angle = angle;
	projectile->power = power;
	projectile->radian = angle * (PI / 180.0f);
	projectile->vel = MakeVec2( power * cosf( projectile->radian ), -power * sinf( projectile->radian ) );
}

void SetProjectile( Projectile* projectile, Vec2 pos )
{
	projectile->time = 0;
	projectile->pos = pos;
	projectile->rect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	projectile->nextRect = projectile->rect;
	projectile->lastPos = pos;
	projectile->startPos = pos;
}

void EndProjectile( Projectile* projectile, Vec2 pos )
{
	projectile->state = ProjWait;
}

bool IsNextProjectileInScreen( Projectile* projectile )
{
	const Rect screenRect = GetScreenRect();
	
	// Check except Screen Top
	return projectile->nextRect.left >= screenRect.left && projectile->nextRect.right <= screenRect.right
		&& projectile->nextRect.bottom <= screenRect.bottom;
}

bool IsOverlapWithTarget( Projectile* projectile, Rect targetRect )
{
	return RectIsOverlappingWith( projectile->rect, targetRect );
}

void SetParabolaForUser( Projectile* projectile )
{
	projectile->nextPos.x = projectile->startPos.x + projectile->power * cosf( projectile->radian ) * projectile->time;
	projectile->nextPos.y = projectile->startPos.y - (float)(projectile->power * sinf( projectile->radian ) * projectile->time
		- (0.5 * G * projectile->time * projectile->time));
	projectile->nextRect = MakeRectBySize( projectile->nextPos, projectile->sprite->width, projectile->sprite->height );
	if ( IsNextProjectileInScreen( projectile ) )
	{
		projectile->pos = projectile->nextPos;
		projectile->rect = projectile->nextRect;
	}
}

void SetParabolaForAI( Projectile* projectile )
{
	projectile->nextPos.x = projectile->startPos.x + (projectile->vel.x * projectile->time);
	projectile->nextPos.y = projectile->startPos.y - ((float)(projectile->vel.y * projectile->time) - (0.5 * projectile->fakeGravity * pow( projectile->time, 2 )));
	projectile->nextRect = MakeRectBySize( projectile->nextPos, projectile->sprite->width, projectile->sprite->height );
	// Screen Check
	if ( IsNextProjectileInScreen(projectile) )
	{
		projectile->pos = projectile->nextPos;
		projectile->rect = projectile->nextRect;
	}
}

void DrawProjectile( Projectile* projectile )
{
	DrawProjectileClip( GetScreenRect(), projectile );
}

void DrawProjectileClip( Rect clip, Projectile* projectile )
{
	//DeleteSizeRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipNonChroma( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite );
}


void DrawProjectileChroma(  Projectile* projectile )
{
	DrawProjectileClipChroma( GetScreenRect(), projectile );
}

void DrawProjectileClipChroma( Rect clip, Projectile* projectile )
{
	//DeleteRect( projectile->rect );
	//DeleteSizeRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipChroma( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite, projectile->chroma );
}


void DrawProjectileColor( Projectile* projectile, Color subColor )
{
	DrawProjectileClipColor( GetScreenRect(), projectile, subColor );
}

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor )
{
	//DeleteSizeRect( SurfaceGetRect( (projectile->sprite) ), (int)projectile->lastPos.x, (int)projectile->lastPos.y );
	DrawSpriteClipSubstitute( (int)projectile->pos.x, (int)projectile->pos.y, SurfaceGetRect((projectile->sprite)), clip, projectile->sprite, projectile->chroma, subColor );
}