#include "Tank.h"

#include "Graphics.h"
#include <stdlib.h>

void MakeTank( Tank* tank, TankType type, int pos_x, Vec2 groundPos )
{
	tank->type = type;
	switch ( type )
	{
	case LightTank:
		MakeSurface( "src/images/tank/player/LightTankGray30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case LightTankAI:
		MakeSurface( "src/images/tank/ai/LightTankGrayFlip30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case MiddleTank:
		MakeSurface( "src/images/tank/player/MiddleTankGray30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case MiddleTankAI:
		MakeSurface( "src/images/tank/ai/MiddleTankGrayFlip30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case HeavyTank:
		MakeSurface( "src/images/tank/player/HeavyTankGray30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case HeavyTankAI:
		MakeSurface( "src/images/tank/ai/HeavyTankGrayFlip30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	case MRL:
		MakeSurface( "src/images/tank/player/MRLGray30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = (float)tank->sprite.width;
		break;
	case MRLAI:
		MakeSurface( "src/images/tank/ai/MRLGrayFlip30.bmp", &(tank->sprite) );
		tank->speed = 10;
		tank->gunPos.x = 0.0f;
		break;
	default:
		break;
	}
	tank->pos.x = (float)pos_x;
	tank->pos.y = groundPos.y - tank->sprite.height;
	

	tank->gunPos.x += tank->pos.x;
	tank->gunPos.y = tank->pos.y;

	tank->rect = MakeRectBySize( tank->pos, tank->sprite.width, tank->sprite.height );
	tank->lastRect = tank->rect;

	tank->state = TankWait;
}

void SetTankAIToMove( Tank* tank )
{
	aiCount = 0;
	aiMaxCount = rand() % 10;

	// Create -1 or 1
	aiDir = ((rand() % 2) * -2) + 1;
	tank->state = TankMove;
}

void UpdateTankAI( Tank* tank )
{
	if ( tank->state == TankMove )
	{
		if ( aiMaxCount <= 10 )
		{
			MoveTankAI( tank );
			aiMaxCount++;
		}
		else
		{
			tank->state = TankWait;
		}
	}
	else if ( tank->state == TankFire )
	{

	}


}

void MoveTank( Tank* tank, Vec2 dir )
{
	const Vec2 nextPos = Vec2Add( (tank->pos), Vec2Mul( dir, (float)tank->speed ) );
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

bool IsTankOverlapWith(Tank* tank, Rect target)
{
	return RectIsOverlappingWith( tank->rect, target );
}

void DrawTank( Tank* tank )
{
	DeleteRect( tank->lastRect );
	DrawSpriteNonChroma( (int)tank->pos.x, (int)tank->pos.y, &(tank->sprite) );
}