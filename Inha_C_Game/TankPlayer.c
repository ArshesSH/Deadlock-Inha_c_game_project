#include "TankPlayer.h"

#include <Windows.h>

void MakeTankPlayer(TankPlayer* pTankPlayer, TankType type, int pos_x, Vec2 groundPos, Rect limitZone)
{
	TankModel* pModel = &(pTankPlayer->model);

	MakeTankModel( pModel, type, pos_x, groundPos, limitZone );
	MakeStatus( &(pTankPlayer->status), pModel->tankMaxHealth, pModel->tankMinAngle,
		pModel->tankMinPower, pModel->tankSpeed );
	MakeProjectilePlayer( &(pTankPlayer->bullet), &(pModel->bulletSprite), MAGENTA, pModel->bulletDamage, pModel->bulletSpeed );
}

void UpdatePlayerTank( TankPlayer* pTankPlayer, Vec2 dir, Rect targetRect, Rect groundRect, Rect groundAIRect )
{
	TankModel* pModel = &(pTankPlayer->model);

	switch (pModel->state)
	{
	case TankMove:
		MoveTank( pModel, dir, pModel->limitZone );
		SetTankStateMove( pModel );
		break;

	case TankFire:
		// If Start Fire, Start Fire effect
		if (GetProjectileState( &(pTankPlayer->bullet.model) ) == ProjWait)
		{
			StartEffect( &(pModel->fireEffect) );
		}
		UpdateProjectilePlayer( &(pTankPlayer->bullet), pModel->gunPos,
			pTankPlayer->status.angle, pTankPlayer->status.power, targetRect, groundRect, groundAIRect);
		UpdateEffect( &(pModel->fireEffect) );
		break;
	}
}

void DestroyTankPlayer( TankPlayer* pTankPlayer )
{
	DestroyTank( &(pTankPlayer->model) );
}