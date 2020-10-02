#pragma once
#include "../GameEvent.h"
#include <Network/server.h>

class CreateEnemyEvent : public GameEvent
{
public:
	float speed;
	float hp;
	float size;
	float armor;
	float shield;
	float regen;
	float progress;
	int tile;
	int birth;
	int death;
	CreateEnemyEvent(int entityKey, int tTick, float speed, float hp, float size, float armor, float shield, float regen, float progress, int tile, int birth, int death) :
		speed(speed),
		hp(hp),
		size(size),
		armor(armor),
		shield(shield),
		regen(regen),
		progress(progress),
		tile(tile),
		birth(birth),
		death(death)
	{
		triggerTick = tTick;
		eventID = CREATE_ENEMY_EVENT_ID;
	};

	void Trigger()
	{

	}

	void OnCreate()
	{
		//This packet can only be created by the server, hence we for sure send it to all people if we are server.
		if (Server::GetInstance().isStarted())
		{
			SendToAll()
		}
	}


};
