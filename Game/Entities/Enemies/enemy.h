#pragma once
#include <Network/SyncedEntity.h>
#include <Network/EntityMgr.h>
#include <Game/clock.h>
#include "../gameentity.h"
#include "../../Tile.h"

class Enemy : public GameEntity
{
public:
	Enemy();
	/*Lennos special testing enemy constructor. Remove once possible*/
	Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, float x, float y, int tile, int birth, int death, vint& path);
	//Actual proper constructor
	Enemy(int entityKey, int level, float speed, float hp, float size, float armor, float shield, float regen, float x, float y, int birthTick, int typeID);
	void Update(int dt);

	int getPath(int index);
	Tile* getNextTile();
	Tile* getCurrentTile();

	float* x;
	float* y;

	int enemyTypeID;
	int* level;
private:
	float* speed;
	float* hp;
	float* size;
	float* armor;
	float* shield;
	float* regen;


	int* tile;


	int* birth;
	int* death;
	int* current_path;

	int path_length;
	int path_sIndex;
	float* progress;
};
