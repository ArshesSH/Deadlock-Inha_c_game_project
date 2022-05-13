#pragma once

#include "Font.h"
#include "SceneType.h"
#include "Tank.h"

typedef struct selectScene
{
	Font title;
	Font discription;
	Surface light;
	Surface medium;
	Surface heavy;
	Surface mrl;
	TankType tankType;
	TankType playerSelection;

	Vec2 posLight;
	Vec2 posMedium;
	Vec2 posHeavy;
	Vec2 posMRL;
	Vec2 posDisc;
}SelectScene;


static char* textLight = "          Light Tank\n\nThis tank is weak, but it can hit the enemy accurately.";
static char* textMedium = "           Medium Tank\n\nThis tank is a medium tank, so it's really in the medium :)";
static char* textHeavy = "           Heavy Tank\n\nThis tank is very defensive, but it's really slow. Really.";
static char* textMRL = "          MRL: Multiple Rocket Launcher\n\n\"Sorry, sir. We're out of missiles you ordered.\"\nIt's likely to fire multiple missiles, like its name and appearance.\nBut the equipment is broken and only one missile can be fired.";

void InitSelectScene( SelectScene* scene );

SceneType UpdateSelectScene( SelectScene* scene );

void DrawSelectScene( SelectScene* scene );

void DestroySelectScene( SelectScene* scene );

void ChooseTank( TankType* current );

