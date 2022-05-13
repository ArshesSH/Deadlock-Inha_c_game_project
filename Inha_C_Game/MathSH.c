#include "MathSH.h"
#include <math.h>

void swapI( int* lhs, int* rhs )
{
	int tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

int MaxI( int lhs, int rhs )
{
	return (lhs > rhs) ? lhs : rhs;
}