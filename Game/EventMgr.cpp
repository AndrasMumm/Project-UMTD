#include "EventMgr.h"
#include <vector>

void EventMgr::Update(GameEntity* entity, int tick)
{
	std::vector<std::multimap<int, GameEvent*>::iterator> toRemove;
	auto it = events.begin();
	while (it != events.end() && it->first <= tick)
	{
		it->second->Trigger(entity, it->first - tick);
		toRemove.push_back(it);
	}

	for (auto it : toRemove)
	{
		events.erase(it);
	}
}

void EventMgr::AddEvent(GameEntity* entity, GameEvent* gameEvent)
{
	gameEvent->OnCreate(entity);
	events.insert({ gameEvent->triggerTick, gameEvent });
}
