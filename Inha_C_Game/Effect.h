#pragma once

#include "Surface.h"

typedef enum effectState
{
	EffectWait,
	EffectPlay
}EffectState;

// Effect Sprite and Sound
typedef struct effect
{
	Surface sprite;
	char* soundFilename;
	Color chorma;
	float playTime;
	float currentTime;
	EffectState state;
}Effect;

void MakeEffect( Effect* effect, const char* spriteFilename, Color chroma, const char* soundFilename, float playTime );

void StartEffect( Effect* effect );

void UpdateEffect( Effect* effect );

void DrawEffect( Effect* effect, Vec2 pos );

void DestroyEffect( Effect* effect );
