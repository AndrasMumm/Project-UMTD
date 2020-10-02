#pragma once
#include <map>
#include <Game\EventSystem\GameEvent.h>

class GameEntity;
class EventMgr
{
private:
	std::multimap<int, GameEvent*> events;

public:
	GameEntity* entity;
	EventMgr(GameEntity* entity) : entity(entity) {};
	void Update(int tick);
	void AddEvent(GameEvent* event);
};
