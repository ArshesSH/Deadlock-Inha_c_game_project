#include "Effect.h"


#include "Graphics.h"

void MakeEffect(Effect* effect, const char* spriteFilename, Color chroma, float playTime)
{
	effect->chorma = chroma;

	MakeSurface( spriteFilename, &(effect->sprite) );
	effect->playTime = playTime;
	effect->currentTime = 0.0f;
	effect->state = EffectWait;
}

void StartEffect( Effect* effect )
{
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
}