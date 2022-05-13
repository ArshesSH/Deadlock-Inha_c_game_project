#pragma once

#include "Status.h"
#include "Font.h"
#include <stdio.h>

typedef struct ui
{
	Status* targetStatus;
	Font textFont;
	Vec2 UIPos;
	Vec2 healthPos;
	Vec2 anglePos;
	Vec2 powerPos;
	char text[BUFSIZ];
}UI;

void MakeUI( UI* ui, Status* target, Vec2 pos );

void UpdateUI( UI* ui );

void DrawUI( UI* ui );

void DrawPlayerUI( UI* ui );

void DrawHealth( UI* ui );

void DestroyUI( UI* ui );
