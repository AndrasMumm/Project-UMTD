#pragma once
#include <Game/clock.h>
#include "gameentity.h"

class Buff
{
public:
	int buffID;
	int level;
	int startTime;
	int duration;
	Buff();
	Buff(int buffID, int level) : buffID(buffID), level(level) {};
};
