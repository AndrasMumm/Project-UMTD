#pragma once
#include "../Enemies/enemy.h"

enum TargetType
{
	CLOSEST,
	FASTEST,
	MAX_HP,
	MAX_VALUE,
	MAX_DMG,
	MOST_TARGETS
};

class Tower
{
public:

	Tower() {};
	~Tower() {};

	virtual void init() = 0;
	virtual void update() = 0;

	int id;
	int lvl;
	float range;
	float dmg;
	float aoe_range;
	float aoe_dmg;
	TargetType targetType;
	Enemy* currentTarget;
	int aa_cd;
	int price;
	int value;
	int kills;
	int sell_value;
};
