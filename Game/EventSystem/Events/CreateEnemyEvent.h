#pragma once
#include "../GameEvent.h"
#include <Network/server.h>

class CreateEnemyEvent : public GameEvent
{
public:
	int triggerTick;
	int entityKey;
	int enemyID;
	int level;
	int eventID;
	float posX;
	float posY;

	CreateEnemyEvent(int tTick, int entityKey, int enemyID, int level, float posX, float posY) :
		triggerTick(tTick),
		entityKey(entityKey),
		enemyID(enemyID),
		level(level),
		posX(posX),
		posY(posY)
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
