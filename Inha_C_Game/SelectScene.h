#pragma once

#include "Font.h"
#include "SceneType.h"
#include "Tank.h"

typedef struct selectScene
{
	Font title;
	Font discription;
	Surface light;
	Surface middle;
	Surface heavy;
	Surface MRL;
	TankType tankType;
	
}SelectScene;

void InitSelectScene( SelectScene* scene );
