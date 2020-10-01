#pragma once
#include <Network\server.h>

class GameEntity;
class GameEvent
{
private:
	bool _sentToAll = false;
public:
	int triggerTick;

	GameEvent() = default;
	virtual ~GameEvent() = 0;
	virtual void trigger(GameEntity* entity, int deltaTickDifference = 0) = 0;
	virtual void onCreate(GameEntity* entity) = 0;

	void SendToAll()
	{
		if (Server::GetInstance().IsStarted())
		{
			//We are server

		}
		else
		{
			//We are client
		}

		_sentToAll = true;
	}

};
