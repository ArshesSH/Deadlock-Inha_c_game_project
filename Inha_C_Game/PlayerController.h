#pragma once

#include <Windows.h>
#include <stdbool.h>

typedef enum playerInput
{
	InputUP,
	InputDown,
	InputLeft,
	InputRight,
	InputEnter,
	InputShift,
	InputCtrl
}PlayerInput;

bool IsPlayerInput( int vKey );