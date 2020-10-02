#pragma once
#include <Network/SyncedEntity.h>
#include <Network/EntityMgr.h>
#include <Game/clock.h>
#include "helpingHeader.h"
#include "Tile.h"
class Enemy : public SyncedEntity
{
public:
	Enemy();
	Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, float x, float y, int tile, int birth, int death,vint& path);

	float* x;
	float* y;

	int getPath(int index);
	Tile* getCurrentTile();
	Tile* getNextTile();

	void update(int dt);

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

	int* current_path;

	int path_sIndex;
	int path_length;



};
