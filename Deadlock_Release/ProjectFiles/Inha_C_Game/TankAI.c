#include "TankAI.h"

#include <stdlib.h>
#include <Windows.h>

void MakeTankAI( TankAI* pTankAI, TankType type, int pos_x, Vec2 groundPos, Rect limitZone, int aiDifficult )
{
	TankModel* pModel = &(pTankAI->model);

	pTankAI->aiOffset = aiDifficult;
	MakeTankModel( pModel, type, pos_x, groundPos, limitZone );
	MakeStatus( &(pTankAI->status), pModel->tankMaxHealth, 0, 0, pModel->tankSpeed );
	MakeProjectileAI( &(pTankAI->bullet), &(pModel->bulletSprite), MAGENTA, pModel->bulletDamage, pModel->bulletSpeed );
}

void UpdateTankAI( TankAI* pTankAI, Vec2 targetPos, Rect targetRect, Rect groundRect, Rect groundAIRect )
{
	TankModel* pModel = &(pTankAI->model);

	switch (pModel->state)
	{
	case TankDrawAndWait:
		SetTankAIMoveCount( pTankAI );
		SetTankStateMove( pModel );
		break;

	case TankMove:
		// Move unitl aiCount less then aiMaxCount
		if (pTankAI->aiCount <= pTankAI->aiMaxCount)
		{
			MoveTank( pModel, MakeVec2( (float)pTankAI->aiDir, 0.0f ), pModel->limitZone );
			pTankAI->aiCount++;
		}
		// Chnge State when Finish Move
		else
		{
			SetTankStateFire( pModel );
		}
		break;

	case TankFire:
		// If Start Fire, Start Fire effect
		if (GetProjectileState( &(pTankAI->bullet.model) ) == ProjWait)
		{
			StartEffect( &(pModel->fireEffect) );
		}
		UpdateProjectileAI( &(pTankAI->bullet), pModel->gunPos, targetPos, pTankAI->aiOffset, targetRect, groundRect, groundAIRect);
		UpdateEffect( &(pModel->fireEffect) );
		break;
	}
}

void SetTankAIMoveCount( TankAI* pTankAI )
{
	pTankAI->aiCount = 0;
	pTankAI->aiMaxCount = rand() % 10;

	// Create -1 or 1
	pTankAI->aiDir = ((rand() % 2) * -2) + 1;
}

void DestroyTankAI( TankAI* pTankAI )
{
	DestroyTank( &(pTankAI->model) );
}