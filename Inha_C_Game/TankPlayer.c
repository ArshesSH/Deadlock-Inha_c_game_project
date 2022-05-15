#include "TankPlayer.h"

void MakeTankPlayer(TankPlayer* pTankPlayer, TankType type, int pos_x, Vec2 groundPos, Rect limitZone)
{
	TankModel* pModel = &(pTankPlayer->model);

	MakeTankModel( pModel, type, pos_x, groundPos, limitZone );
	MakeStatus( &(pTankPlayer->status), pModel->tankMaxHealth, pModel->tankMinAngle,
		pModel->tankMinPower, pModel->tankSpeed );
	MakeProjectilePlayer( &(pTankPlayer->bullet), &(pModel->bulletSprite), MAGENTA, pModel->bulletDamage );
}

void UpdatePlayerTank( TankPlayer* pTankPlayer, Vec2 dir, Rect targetRect, Rect groundRect )
{
	TankModel* pModel = &(pTankPlayer->model);
	// Tank Move State
	if (pModel->state == TankMove)
	{
		MoveTank( pModel, dir, pModel->limitZone );
		SetTankStateMove( pModel );
	}
	// Tank Fire State
	else if (pModel->state == TankFire)
	{
		UpdateProjectilePlayer( &(pTankPlayer->bullet), pModel->gunPos,
			pTankPlayer->status.angle, pTankPlayer->status.power, targetRect, groundRect );
	}
	else if (pModel->state == TankDamaged)
	{
		//play Effect

	}
}

ProjectileState GetPlayerBulletState( TankPlayer* pTankPlayer )
{
	return pTankPlayer->bullet.model.state;
}