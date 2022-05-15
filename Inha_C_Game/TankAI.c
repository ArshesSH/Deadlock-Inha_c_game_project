#include "TankAI.h"

#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void MakeTankAI( TankAI* pTankAI, TankType type, int pos_x, Vec2 groundPos, Rect limitZone, int aiDifficult )
{
	TankModel* pModel = &(pTankAI->model);

	pTankAI->aiOffset = aiDifficult;
	MakeTankModel( pModel, type, pos_x, groundPos, limitZone );
	MakeStatus( &(pTankAI->status), pModel->tankMaxHealth, 0, 0, pModel->tankSpeed );
	MakeProjectileAI( &(pTankAI->bullet), &(pModel->bulletSprite), MAGENTA, pModel->bulletDamage );
}

void UpdateTankAI( TankAI* pTankAI, Vec2 targetPos, Rect targetRect, Rect groundRect )
{
	TankModel* pModel = &(pTankAI->model);
	if (pModel->state == TankDrawAndWait)
	{
		SetTankAIMoveCount( pTankAI );
		SetTankStateMove( pModel );
	}
	else if (pModel->state == TankMove)
	{
		if (pTankAI->aiCount <= pTankAI->aiMaxCount)
		{
			MoveTank( pModel, MakeVec2( (float)pTankAI->aiDir, 0.0f ), pModel->limitZone );
			pTankAI->aiCount++;
		}
		else
		{
			SetTankStateFire( pModel );
		}
	}
	else if (pModel->state == TankFire)
	{
		if (GetProjectileState( &(pTankAI->bullet.model) ) == ProjWait)
		{
			StartEffect( &(pModel->fireEffect) );
		}
		UpdateProjectileAI( &(pTankAI->bullet), pModel->gunPos, targetPos, pTankAI->aiOffset, targetRect, groundRect );
		UpdateEffect( &(pModel->fireEffect) );
	}
	else if (pModel->state == TankDamaged)
	{
		PlaySound( TEXT( "src/sounds/explosion.wav" ), NULL, SND_ASYNC );
		// play effects;
		pModel->hitPos.x = pModel->pos.x;
		StartEffect( &(pModel->hitEffect) );
		pModel->state = TankWait;
	}

}

void SetTankAIMoveCount( TankAI* pTankAI )
{
	pTankAI->aiCount = 0;
	pTankAI->aiMaxCount = rand() % 10;

	// Create -1 or 1
	pTankAI->aiDir = ((rand() % 2) * -2) + 1;
}

ProjectileState GetAIBulletState( TankAI* pTankAI )
{
	return pTankAI->bullet.model.state;
}

void DestroyTankAI( TankAI* pTankAI )
{
	DestroyTank( &(pTankAI->model) );
}