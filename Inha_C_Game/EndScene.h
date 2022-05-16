#pragma once

#include "Font.h"
#include "Surface.h"
#include "SceneType.h"
#include "PlayerController.h"

typedef struct endScene
{
	Font title;
	Font script;
	Font guide;
}EndScene;

void InitEndScene( EndScene* scene );

SceneType UpdateEndScene( EndScene* scene );

void DestroyEndScene( EndScene* scene );
