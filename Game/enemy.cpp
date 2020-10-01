#include "enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, int tile, int birth, int death)
{
	//ToDo get synced from entity mgr

	this->syncedMirror = EntityMgr::getInstance().createSyncedEntity();


	syncedData<float> sync_speed = syncedData<float>();
	sync_speed.flag = true;
	sync_speed.lastSyncedAt = TICK;
	sync_speed.syncFreq = 50;
	sync_speed.value = speed;
	this->speed = syncedMirror->addSyncedData(sync_speed);


	syncedData<float> sync_hp = syncedData<float>();
	sync_hp.flag = true;
	sync_hp.lastSyncedAt = TICK;
	sync_hp.syncFreq = 50;
	sync_hp.value = speed;
	this->hp = syncedMirror->addSyncedData(sync_hp);


	syncedData<float> sync_size = syncedData<float>();
	sync_size.flag = true;
	sync_size.lastSyncedAt = TICK;
	sync_size.syncFreq = 50;
	sync_size.value = speed;
	this->size = syncedMirror->addSyncedData(sync_size);


	syncedData<float> sync_armor = syncedData<float>();
	sync_armor.flag = true;
	sync_armor.lastSyncedAt = TICK;
	sync_armor.syncFreq = 50;
	sync_armor.value = speed;
	this->armor = syncedMirror->addSyncedData(sync_armor);


	syncedData<float> sync_shield = syncedData<float>();
	sync_shield.flag = true;
	sync_shield.lastSyncedAt = TICK;
	sync_shield.syncFreq = 50;
	sync_shield.value = speed;
	this->shield = syncedMirror->addSyncedData(sync_shield);


	syncedData<float> sync_regen = syncedData<float>();
	sync_regen.flag = true;
	sync_regen.lastSyncedAt = TICK;
	sync_regen.syncFreq = 50;
	sync_regen.value = speed;
	this->regen = syncedMirror->addSyncedData(sync_regen);


	syncedData<float> sync_progress = syncedData<float>();
	sync_progress.flag = true;
	sync_progress.lastSyncedAt = TICK;
	sync_progress.syncFreq = 50;
	sync_progress.value = speed; 
	this->progress = syncedMirror->addSyncedData(sync_progress);
}



Enemy::~Enemy()
{
}
