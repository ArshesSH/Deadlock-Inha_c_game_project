#include "MathSH.h"
#include <math.h>

void swapI( int* lhs, int* rhs )
{
	int tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}