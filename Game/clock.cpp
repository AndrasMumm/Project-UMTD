#include "clock.h"

int Clock::getTick()
{
	return tock;
}

void Clock::tick()
{
	++tock;
}
