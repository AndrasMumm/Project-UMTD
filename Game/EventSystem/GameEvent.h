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
	int ownerEntityKey;
	int triggerTick;
	int eventID;

	GameEvent(int ownerEntityKey, int triggerTick, int eventID) : ownerEntityKey(ownerEntityKey), triggerTick(triggerTick), eventID(eventID) {};
	~GameEvent() {};
	virtual void Trigger(GameEntity* entity, int deltaTickDifference = 0) = 0;
	virtual void OnCreate(GameEntity* entity) = 0;

	void SendToAll();
};
