#include "MathSH.h"
#include <math.h>

void swapI( int* lhs, int* rhs )
{
	int tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

float MaxF( float lhs, float rhs )
{
	return (lhs > rhs) ? lhs : rhs;
}

float MinF( float lhs, float rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}