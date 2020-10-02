#pragma once
#include <Network/SyncedEntity.h>
#include <Network/EntityMgr.h>
#include <Game/clock.h>
#include "gameentity.h"
#include "Tile.h"

class Enemy : public GameEntity
{
public:
	Enemy();
	Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, float x, float y, int tile, int birth, int death, vint& path);

	void update(int dt);

	int getPath(int index);
	Tile* getNextTile();
	Tile* getCurrentTile();

	float* x;
	float* y;

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
	int* current_path;

	int path_length;
	int path_sIndex;
};
