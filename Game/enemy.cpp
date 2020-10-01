#include "enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, int tile, int birth, int death)
{

	syncedData<float> sync_speed = syncedData<float>();
	sync_speed.flag = true;
	sync_speed.lastSyncedAt = TICK;
	sync_speed.syncFreq = 50;
	sync_speed.value = speed;
	this->speed = this->addSyncedData(sync_speed);


	syncedData<float> sync_hp = syncedData<float>();
	sync_hp.flag = true;
	sync_hp.lastSyncedAt = TICK;
	sync_hp.syncFreq = 50;
	sync_hp.value = hp;
	this->hp = this->addSyncedData(sync_hp);


	syncedData<float> sync_size = syncedData<float>();
	sync_size.flag = true;
	sync_size.lastSyncedAt = TICK;
	sync_size.syncFreq = 50;
	sync_size.value = size;
	this->size = this->addSyncedData(sync_size);


	syncedData<float> sync_armor = syncedData<float>();
	sync_armor.flag = true;
	sync_armor.lastSyncedAt = TICK;
	sync_armor.syncFreq = 50;
	sync_armor.value = armor;
	this->armor = this->addSyncedData(sync_armor);


	syncedData<float> sync_shield = syncedData<float>();
	sync_shield.flag = true;
	sync_shield.lastSyncedAt = TICK;
	sync_shield.syncFreq = 50;
	sync_shield.value = shield;
	this->shield = this->addSyncedData(sync_shield);


	syncedData<float> sync_regen = syncedData<float>();
	sync_regen.flag = true;
	sync_regen.lastSyncedAt = TICK;
	sync_regen.syncFreq = 50;
	sync_regen.value = regen;
	this->regen = this->addSyncedData(sync_regen);


	syncedData<float> sync_progress = syncedData<float>();
	sync_progress.flag = true;
	sync_progress.lastSyncedAt = TICK;
	sync_progress.syncFreq = 50;
	sync_progress.value = progress; 
	this->progress = this->addSyncedData(sync_progress);


	syncedData<int> sync_tile = syncedData<int>();
	sync_tile.flag = true;
	sync_tile.lastSyncedAt = TICK;
	sync_tile.syncFreq = 50;
	sync_tile.value = tile;
	this->tile = this->addSyncedData(sync_tile);



	syncedData<int> sync_birth = syncedData<int>();
	sync_birth.flag = true;
	sync_birth.lastSyncedAt = TICK;
	sync_birth.syncFreq = 50;
	sync_birth.value = birth;
	this->birth = this->addSyncedData(sync_birth);

	syncedData<int> sync_death = syncedData<int>();
	sync_death.flag = true;
	sync_death.lastSyncedAt = TICK;
	sync_death.syncFreq = 50;
	sync_death.value = death;
	this->death = this->addSyncedData(sync_death);



}

