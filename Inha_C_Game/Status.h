#pragma once

typedef enum statusChanged
{
	NoChange,
	ChangeHealth,
	ChangeAngle,
	ChangePower
}StatusChanged;

typedef struct status
{
	float maxHelath;
	float health;
	float healthPercentage;
	StatusChanged statusChange;
	int angle;
	int power;
	int speed;
}Status;

void MakeStatus( Status* status, float maxHealth, int angle, int power, int speed );

void CalcStatusHealth( Status* status, float damage );

void SetStatusAngle( Status* status, int angle );

void SetStatusPower( Status* status, int power );

void SetStatusSpeed( Status* status, int speed );
