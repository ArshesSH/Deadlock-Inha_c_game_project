#include "Effect.h"

#include <stdlib.h>
#include <string.h>
#include "Graphics.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void MakeEffect(Effect* effect, const char* spriteFilename, Color chroma, const char* soundFilename, float playTime)
{
	const size_t soundFilenameSize = strlen( soundFilename ) + 1;
	effect->soundFilename = (char*)malloc( soundFilenameSize + 1 );
	strcpy_s( effect->soundFilename, soundFilenameSize, soundFilename );
	effect->chorma = chroma;

	MakeSurface( spriteFilename, &(effect->sprite) );
	effect->playTime = playTime;
	effect->currentTime = 0.0f;
}

void StartEffect( Effect* effect )
{
	PlaySound( effect->soundFilename, NULL, SND_ASYNC );
	effect->state = EffectPlay;
}

void UpdateEffect( Effect* effect )
{
	if ( effect->state == EffectPlay )
	{
		// Reset Effect
		if ( effect->currentTime >= effect->playTime )
		{
			effect->currentTime = 0;
			effect->state = EffectWait;
		}
		else
		{
			effect->currentTime += 0.1f;
		}
	}
}

void DrawEffect( Effect* effect, Vec2 pos )
{
	if ( effect->state == EffectPlay )
	{
		if ( effect->currentTime >= effect->playTime )
		{
			DeleteSizeRect( SurfaceGetRect( &(effect->sprite) ), (int)pos.x, (int)pos.y );
		}
		else
		{
			DrawSpriteChroma( (int)pos.x, (int)pos.y, &(effect->sprite), effect->chorma );
		}
	}
}

void DestroyEffect( Effect* effect )
{
	DestroySurface( &(effect->sprite) );
	free( effect->soundFilename );
}