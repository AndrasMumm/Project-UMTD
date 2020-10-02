#pragma once
#include <Network\server.h>
#include <Network\client.h>
#include <Network\Packets\Events\CreateEvent.h>
#include <Game\EventSystem\EventList.h>
class GameEntity;

class GameEvent
{
private:
	bool _sentToAll = false;

public:
	int triggerTick;
	int eventID;
	int authorID;

	GameEvent() = default;
	virtual ~GameEvent() = 0;
	virtual void Trigger(GameEntity* entity, int deltaTickDifference = 0) = 0;
	virtual void OnCreate(GameEntity* entity) = 0;

	void SendToAll(GameEntity* entity);
};
