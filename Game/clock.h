#pragma once

#include <vector>
#include <Network/SyncedEntity.h>

#define TICK Clock::getInstance().getTick()
#define TIME Clock::getInstance().getCurrentSystemTime()
#define TICK_TIME_MS 1000ll

class Clock
{
public:
	static Clock& getInstance()
	{
		static Clock instance;

		return instance;
	}
	int getTick();
	void tick();
	long long getCurrentSystemTime();
private:
	Clock() {}

	int tock;



public:
	Clock(Clock const&) = delete;
	void operator=(Clock const&) = delete;

};
