#include "EventMgr.h"
#include <vector>
#include <Game\clock.h>

void EventMgr::Update(int tick)
{
	std::vector<std::multimap<int, GameEvent*>::iterator> toRemove;
	auto it = events.begin();
	while (it != events.end() && it->first <= TICK)
	{
		it->second->Trigger(entity, it->first - TICK);
		toRemove.push_back(it);
	}

	for (auto it : toRemove)
	{
		auto ptr = it->second;
		events.erase(it);
		delete ptr;
	}
}

void EventMgr::AddEvent(GameEvent* gameEvent)
{
	events.insert({ gameEvent->triggerTick, gameEvent });
	gameEvent->OnCreate(entity);
}
