#include "enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, int tile, int birth, int death) 
{
	//ToDo get synced from entity mgr

	this->syncedMirror = new SyncedEntity();


	syncedData<float> sync_speed = syncedData<float>();
	sync_speed.flag = true;
	sync_speed.lastSyncedAt = 
	this->speed = syncedMirror->addSyncedData(sync_speed);

}



Enemy::~Enemy()
{
}
