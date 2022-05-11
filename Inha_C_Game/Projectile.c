#include "Projectile.h"

#include "Graphics.h"
#include "MathSH.h"
#include <math.h>

void MakeProjectile(Projectile* projectile, Vec2 startPos_in, int angle, int power, Surface* sprite, Color chroma)
{
	// Set Projectile Start Position
	projectile->startPos = startPos_in;
	projectile->pos = startPos_in;
	projectile->lastPos = startPos_in;

	// Get Radian from angle, and make Velocity Vec2
	projectile->radian = angle * (PI / 180.0);
	projectile->angle = angle;
	projectile->power = power;

	// Set Image of projectile
	projectile->sprite = sprite;
	projectile->spriteRect = MakeRectBySize( projectile->pos, sprite->width, sprite->height );

	// Set Image Chroma
	projectile->chroma = chroma;
	projectile->isFired = false;

	// Set Time
	projectile->time = 0.0f;
	projectile->timeCmx = 0.0f;
}


void SetProjectileVel( Projectile* projectile, int angle, int power)
{
	// Get Radian from angle, and make Velocity Vec2
	projectile->radian = angle * (PI / 180.0);
	projectile->vel = MakeVec2( power * cosf( projectile->radian ), -power * sinf( projectile->radian ) );
}

void StartFire(Projectile* projectile)
{
	projectile->isFired = true;
	projectile->lastPos = projectile->startPos;
}

void UpdateProjectile( Projectile* projectile )
{
	projectile->lastPos = projectile->pos;
	projectile->spriteRect = MakeRectBySize( projectile->pos, projectile->sprite->width, projectile->sprite->height );
	SetParabolaForUser( projectile );
	projectile->time += 0.1;
}

void ResetProjectile( Projectile* projectile )
{
	projectile->pos = projectile->startPos;
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

void DrawProjectile( Projectile* projectile )
{
	DrawProjectileClip( GetScreenRect(), projectile );
}

void DrawProjectileClip( Rect clip, Projectile* projectile )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), projectile->lastPos.x, projectile->lastPos.y );
	DrawSpriteClipNonChroma( projectile->pos.x, projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite );
}


void DrawProjectileChroma(  Projectile* projectile )
{
	DrawProjectileClipChroma( GetScreenRect(), projectile );
}

void DrawProjectileClipChroma( Rect clip, Projectile* projectile )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), projectile->lastPos.x, projectile->lastPos.y );
	DrawSpriteClipChroma( projectile->pos.x, projectile->pos.y, SurfaceGetRect( (projectile->sprite) ), clip, projectile->sprite, projectile->chroma );
}


void DrawProjectileColor( Projectile* projectile, Color subColor )
{
	DrawProjectileClipColor( GetScreenRect(), projectile, subColor );
}

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor )
{
	DeleteRect( SurfaceGetRect( (projectile->sprite) ), projectile->lastPos.x, projectile->lastPos.y );
	DrawSpriteClipSubstitute( projectile->pos.x, projectile->pos.y, SurfaceGetRect((projectile->sprite)), clip, projectile->sprite, projectile->chroma, subColor );
}