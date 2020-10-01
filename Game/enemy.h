#pragma once
#include <Network/SyncedEntity.h>
#include <Network/EntityMgr.h>
#include <Game/clock.h>

class Enemy
{
public:
	Enemy();
	Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, int tile, int birth, int death);
	~Enemy();

private:
	float* speed;
	float* hp;
	float* size;
	float* armor;
	float* shield;
	float* regen;
	float* progress;

	int* tile;


	int* birth;
	int* death;

	SyncedEntity* syncedMirror;

};
