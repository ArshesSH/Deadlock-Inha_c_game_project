#pragma once

#include "Vec2.h"
#include "Colors.h"
#include "Surface.h"

typedef struct font
{
	Vec2 pos;
	int fontWidth;
	int fontHeight;
	Color chroma;
	Surface fontTable;

}Font;