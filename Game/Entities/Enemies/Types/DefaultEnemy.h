#pragma once
#include "../enemy.h"
#include "../EnemyTypeID.h"
class DefaultEnemy : public Enemy
{
private:
	float defaultSpeed = 1.0f;
	float defaultHp = 100.0f;
	float defaultSize = 1.0f;
	float defaultArmor = 5.0f;
	float defaultShield = 0.0f;
	float defaultRegen = 0.0f;
public:
	DefaultEnemy(int entityKey, int level, float posX, float posY, int birthTick) : Enemy(entityKey, level, defaultSpeed, defaultHp, defaultSize, defaultArmor, defaultShield, defaultRegen, posX, posY, birthTick, ENEMY_TYPE_DEFAULT) {};
	~DefaultEnemy() = default;
};
