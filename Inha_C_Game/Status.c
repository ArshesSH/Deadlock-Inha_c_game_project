#include "Status.h"

#include "MathSH.h"

void MakeStatus( Status* status, float maxHealth, int angle, int power, int speed )
{
	status->maxHelath = maxHealth;
	status->health = maxHealth;
	status->healthPercentage = 100.0f;
	status->angle = angle;
	status->power = power;
	status->speed = speed;
	status->statusChange = NoChange;
}

void CalcStatusHealth( Status* status, float damage )
{
	status->health = MaxF( status->health - damage, 0 );
	status->healthPercentage = status->health / status->maxHelath * status->healthPercentage;
	status->statusChange = ChangeHealth;
	if ( IsActorDead( status->health ) )
	{
		status->statusChange = ActorDead;
	}
}

void SetStatusAngle( Status* status, int angle )
{
	status->angle = angle;
	status->statusChange = ChangeAngle;
}

void SetStatusPower( Status* status, int power )
{
	status->power = power;
	status->statusChange = ChangePower;
}

void SetStatusSpeed( Status* status, int speed )
{
	status->speed = speed;
}

void ChangeStatusState( Status* status, StatusChanged state )
{
	status->statusChange = state;
}

bool IsActorDead( float health )
{
	return health == 0;
}