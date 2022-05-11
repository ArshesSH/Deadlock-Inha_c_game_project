#include "Character.h"

#include <stdlib.h>

void MakeCharacter( Character* character, Vec2 pos, int spriteStartX, int spriteStartY, int width, int height, int sectionCount, Color chroma, const char* filename )
{
	MakeSurface( filename, &(character->sprite) );
	character->pos = pos;
	character->chroma = chroma;
	character->holdTime = 0.2f;
	character->speed = 10;

	character->animations = (Animation*)malloc( sizeof( Animation ) * Count );

	for (int i = 0; i < (int)StandLeft; i++)
	{
		MakeAnimation( &(character->animations[i]), spriteStartX, i * spriteStartY, width, height, sectionCount,
			&(character->sprite), character->holdTime, character->chroma );

		//animations.emplace_back( 90, i * 90, 90, 90, 4, sprite, 0.2f );
	}
	for (int i = (int)StandLeft; i < (int)Count; i++)
	{
		MakeAnimation( &(character->animations[i]), 0, (i - (int)StandLeft) * spriteStartY, width, height, 1,
			&(character->sprite), character->holdTime, character->chroma );

		//animations.emplace_back( 0, (i - (int)Sequence::StandLeft) * 90, 90, 90, 1, sprite, 0.2f );
	}
}

void DrawCharacter( Character* chara )
{
	DrawAnimeChroma( chara->pos, &(chara->animations[(int)chara->curSequence]) );
}

void SetCharacterDirection( Character* chara, Vec2 dir )
{
	if (dir.x < 0)
	{
		chara->curSequence = WalkLeft;
	}
	else if (dir.x > 0)
	{
		chara->curSequence = WalkRight;
	}
	else if (dir.y < 0)
	{
		chara->curSequence = WalkUp;
	}
	else if (dir.y > 0)
	{
		chara->curSequence = WalkDown;
	}
	else
	{
		if (chara->vel.x < 0)
		{
			chara->curSequence = StandLeft;
		}
		else if (chara->vel.x > 0)
		{
			chara->curSequence = StandRight;
		}
		else if (chara->vel.y < 0)
		{
			chara->curSequence = StandUp;
		}
		else if (chara->vel.y > 0)
		{
			chara->curSequence = StandDown;
		}
	}
	chara->vel = Vec2Mul( GetVec2Normalized( dir ), chara->speed );
}

void UpdateCharacter( Character* chara, float dt )
{
	Vec2AddEqual( &(chara->pos), Vec2Mul( chara->vel, (int)dt ) );
	//UpdateAnimation( &(chara->animations[(int)chara->curSequence]), dt );
	AdvanceImage( &(chara->animations[(int)chara->curSequence]) );
}


void DestroyCharacter( Character* character )
{
	DestroySurface( &(character->sprite) );

	DestroyAnimation( character->animations );
	free( character->animations );
	character->animations = NULL;
}