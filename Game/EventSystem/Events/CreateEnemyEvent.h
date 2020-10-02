#pragma once
#include "../GameEvent.h"
#include <Network/server.h>
#include <Game/Entities/Enemies/EnemyFactory.h>
#include <Game\Entities\HardcodedEntityKeys.h>

class CreateEnemyEvent : public GameEvent
{
public:
	int enemyEntityKey;
	int enemyID;
	int level;
	float posX;
	float posY;

	CreateEnemyEvent(int tTick, int enemyEntityKey, int enemyID, int level, float posX, float posY) :
		GameEvent(GAMESTATE_ENTITY_KEY, tTick, eventID),
		enemyEntityKey(enemyEntityKey),
		enemyID(enemyID),
		level(level),
		posX(posX),
		posY(posY)
	{};
	~CreateEnemyEvent() {}

	void Trigger(GameEntity* entity, int deltaTickDifference);

	void OnCreate(GameEntity* entity);
};
