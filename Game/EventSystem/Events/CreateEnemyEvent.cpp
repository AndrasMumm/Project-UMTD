#include "CreateEnemyEvent.h"
#include <Game/gamestate.h>


void CreateEnemyEvent::Trigger(GameEntity* entity, int deltaTickDifference) {
	//Creating the defined enemy
	Enemy* enemy = EnemyFactory::GenerateEnemy(enemyEntityKey, enemyID, level, posX, posY, triggerTick);
	GameState::getInstance().enemys.push_back(enemy);
}

void CreateEnemyEvent::OnCreate(GameEntity* entity)
{
	//This packet can only be created by the server, hence we for sure send it to all people if we are server.
	if (Server::GetInstance().IsStarted())
	{
		SendToAll();
	}
}
