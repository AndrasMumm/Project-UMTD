#pragma once
#include "../GameEvent.h"
#include <Network/server.h>

#define NOT_SET_ENTITY_KEY -1

class CreateEnemyEvent : public GameEvent
{
public:
	int triggerTick;
	int entityKey;
	int enemyID;
	int level;
	int eventID;

	CreateEnemyEvent(int tTick, int entityKey, int enemyID, int level) :
		triggerTick(tTick),
		entityKey(entityKey),
		enemyID(enemyID),
		level(level)
	{
		eventID = CREATE_ENEMY_EVENT_ID;
	};

	void Trigger()
	{

	}

	void OnCreate()
	{
		//This packet can only be created by the server, hence we for sure send it to all people if we are server.
		if (Server::GetInstance().IsStarted())
		{
			SendToAll(entityKey);
		}
	}
};
