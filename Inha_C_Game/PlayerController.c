#include "PlayerController.h"

#include <Windows.h>
bool IsPlayerInput( int vKey )
{
	return GetAsyncKeyState( vKey ) & 0x8000;
}