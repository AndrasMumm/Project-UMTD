#include "EnemyFactory.h"
#include "EnemyTypeID.h"
#include "Types/DefaultEnemy.h"
#include <Network/server.h>
#include <Game\EventSystem\Events\CreateEnemyEvent.h>
#include <Game\gamestate.h>

Enemy* EnemyFactory::GenerateEnemy(int entityKey, int enemyID, int level, float posX, float posY, int birthTick)
{
	Enemy* enemy;
	switch (enemyID)
	{
	case ENEMY_TYPE_DEFAULT:
		enemy = new DefaultEnemy(entityKey, posX, posY, birthTick, level);
		break;
	default:
		enemy = nullptr;
		break;
	}

	std::cout << "Generated enemy with entityKey " << entityKey << std::endl;
	return enemy;
}

void EnemyFactory::SpawnNewEnemy(int enemyID, int level, float posX, float posY, int birthTick)
{
	if (Server::GetInstance().IsStarted())
	{
		auto createEnemyEvent = new CreateEnemyEvent(birthTick, EntityMgr::getInstance().getNextEntityKey(), enemyID, level, posX, posY);
		GameState::getInstance().eventManager.AddEvent(createEnemyEvent);
	}
	else
	{
		std::cout << "ERROR: Client cannot spawn new enemies." << std::endl;
	}
}
