#pragma once
#include "enemy.h"

class EnemyFactory
{
public:
	static Enemy* GenerateEnemy(int entityKey, int enemyID, int level, float posX, float posY, int birthTick);
	static void SpawnNewEnemy(int enemyID, int level, float posX, float posY, int birthTick);
};
