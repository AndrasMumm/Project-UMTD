#include "clock.h"
#include <chrono>
#include <time.h>

int Clock::getTick()
{
	return tock;
}

void Clock::tick()
{
	++tock;
}

long long Clock::getCurrentSystemTime()
{
	auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
