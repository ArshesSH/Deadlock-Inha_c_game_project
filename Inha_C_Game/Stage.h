#pragma once

#include "Ground.h"
#include "Tank.h"
#include "Font.h"

typedef enum stageType
{
	StageStart,
	Stage1,
	Stage2,
	Stage3,
	StageEnd
}StageType;

typedef struct stage
{
	StageType stage;
	Ground ground;
	Tank player;
	Tank ai;
	
}Stage;