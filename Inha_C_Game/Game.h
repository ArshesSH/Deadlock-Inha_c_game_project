#pragma once

#include "Vec2.h"
#include "Surface.h"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void PlayGame();

void InitGame();

void UpdateModel();

void ComposeFrame();

void EndGame();

// Variable
static const int speed = 1;
Vec2 pos;
Vec2 lastPos;
Vec2 up;
Vec2 down;
Vec2 left;
Vec2 right;
Surface surf;