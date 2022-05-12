#include "Tank.h"

#include "Graphics.h"
#include <stdlib.h>

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos )
{
	tank->type = type;
	switch ( type )
	{
	case LightTank:
		MakeSurface( "src/images/tank/player/LightTankGray40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = tank->sprite.width;
		break;
	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0;
		break;
	case MiddleTank:
		MakeSurface( "src/images/tank/player/MiddleTankGray40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = tank->sprite.width;
		break;
	case MiddleTankAI:
		MakeSurface( "src/images/tank/ai/MiddleTankGrayFlip40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0;
		break;
	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = tank->sprite.width;
		break;
	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0;
		break;
	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = tank->sprite.width;
		break;
	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip40.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0;
		break;
	default:
		break;
	}
	tank->pos.x = pos_x;
	tank->pos.y = groundPos.y - tank->sprite.height;
	

	tank->gunPos.x += tank->pos.x;
	tank->gunPos.y = tank->pos.y;

	tank->isMoving = false;

	tank->rect = MakeRectBySize( tank->pos, tank->sprite.width, tank->sprite.height );
	tank->lastRect = tank->rect;
}

void SetTankAI( Tank* tank )
{
	tank->isMoving = true;
	aiCount = 0;
	aiMaxCount = rand() % 10;

	// Create -1 or 1
	aiDir = ((rand() % 2) * -2) + 1;
}

void UpdateTankAI( Tank* tank )
{
	if ( aiMaxCount <= 10 )
	{
		MoveTankAI( tank );
		aiMaxCount++;
	}
	else
	{
		tank->isMoving = false;
	}
}

void MoveTank( Tank* tank, Vec2 dir )
{
	const Vec2 nextPos = Vec2Add( (tank->pos), Vec2Mul( dir, tank->speed ) );
	const Rect nextRect = MakeRectBySize( nextPos, tank->sprite.width, tank->sprite.height );

	tank->lastRect = tank->rect;

	// Screen Check
	if ( RectIsContainedBy( nextRect, GetScreenRect() ) )
	{
		tank->pos = nextPos;
		tank->rect = nextRect;
	}
}


void MoveTankAI( Tank* tank )
{
	MoveTank( tank, MakeVec2( (float)aiDir, 0.0f ) );
}

void IsTankOverlapWith(Tank* tank, Rect target)
{
	return RectIsOverlappingWith( tank->rect, target );
}

void DrawTank( Tank* tank )
{
	DeleteRect( tank->lastRect );
	DrawSpriteNonChroma( (int)tank->pos.x, (int)tank->pos.y, &(tank->sprite) );
}