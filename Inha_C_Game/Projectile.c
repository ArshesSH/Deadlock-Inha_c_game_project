#include "Projectile.h"

#include "Graphics.h"
#include "MathSH.h"
#include <math.h>

void MakeProjectile(Projectile* projectile, Vec2 startPos_in, int angle, int power, Surface* sprite, Color chroma)
{
	// Set Projectile Start Position
	projectile->startPos = startPos_in;
	projectile->pos = startPos_in;

	// Get Radian from angle, and make Velocity Vec2
	float radian = angle * (PI / 180.0);

	// Set Image of projectile
	projectile->sprite = sprite;

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
	float radian = angle * (PI / 180.0);
	projectile->vel = MakeVec2( power * cosf( radian ), -power * sinf( radian ) );
}

void StartFire(Projectile* projectile)
{
	projectile->isFired = true;
}

void UpdateProjectile( Projectile* projectile, Rect targetRect )
{

}

void ResetProjectile( Projectile* projectile )
{
	projectile->pos = projectile->startPos;
	projectile->isFired = false;
}

bool IsInScreen( Projectile* projectile )
{
	const Rect screenRect = GetScreenRect();
	const Rect projRect = SurfaceGetRect( projectile->sprite );

	// Check except Screen Top
	return projRect.left >= projRect.left && projRect.right <= projRect.right
		&& projRect.bottom <= projRect.bottom;
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


void DrawProjectile( Projectile* projectile )
{
	DrawProjectileClip( GetScreenRect(), projectile );
}

void DrawProjectileClip( Rect clip, Projectile* projectile )
{
	DrawSpriteClipNonChroma( projectile->pos.x, projectile->pos.y, SurfaceGetRect( projectile->sprite ), clip, projectile->sprite );
}


void DrawProjectileChroma(  Projectile* projectile )
{
	DrawProjectileClipChroma( GetScreenRect(), projectile );
}

void DrawProjectileClipChroma( Rect clip, Projectile* projectile )
{
	DrawSpriteClipChroma( projectile->pos.x, projectile->pos.y, SurfaceGetRect( projectile->sprite ), clip, projectile->sprite, projectile->chroma );
}


void DrawProjectileColor( Projectile* projectile, Color subColor )
{
	DrawProjectileClipColor( GetScreenRect(), projectile, subColor );
}

void DrawProjectileClipColor( Rect clip, Projectile* projectile, Color subColor )
{
	DrawSpriteClipSubstitute( projectile->pos.x, projectile->pos.y, SurfaceGetRect( projectile->sprite ), clip, projectile->sprite, projectile->chroma, subColor );
}