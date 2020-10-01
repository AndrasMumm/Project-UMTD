#pragma once
#include <map>
#include <Game\EventSystem\GameEvent.h>
#include <Game\gameentity.h>
class EventMgr
{
private:
	std::multimap<int, GameEvent*> events;

public:
	void Update(GameEntity* entity, int tick);
	void AddEvent(GameEntity* entity, GameEvent* event);
};
