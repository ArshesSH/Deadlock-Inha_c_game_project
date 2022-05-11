#include "FrameTimer.h"


void StartFrameTimer( time_t* last )
{
	//time( last );
	*last = clock();
}

float MarkFrameTimer( time_t* last )
{
	const time_t old = *last;
	//time( last );
	*last = clock();
	return (float)(*last - old) / CLOCKS_PER_SEC;
}