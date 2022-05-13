#include "Status.h"

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
	status->health -= damage;
	status->healthPercentage = status->health / status->maxHelath * status->healthPercentage;
}

void SetStatusAngle( Status* status, int angle )
{
	status->angle = angle;
}

void SetStatusPower( Status* status, int power )
{
	status->power = power;
}

void SetStatusSpeed( Status* status, int speed )
{
	status->speed = speed;
}