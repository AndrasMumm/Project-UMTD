#include "SyncedEntity.h"
#include "EntityMgr.h"
using namespace std;


SyncedEntity::SyncedEntity(int entityKey) : entityKey(entityKey) {

}

SyncedEntity::~SyncedEntity()
{
	EntityMgr::getInstance().removeSyncedEntity(this);

	for (syncedData<int>* p : syncedInts) {
		delete p;
	}
	for (syncedData<float>* p : syncedFloat) {
		delete p;
	}
	for (syncedData<string>* p : syncedString) {
		delete p;
	}
}
void SyncedEntity::Update(int delta) {};
void SyncedEntity::ReceiveSync(SyncDataPacket* packet) {};

void SyncedEntity::addSyncedData(syncedData<int>* data)
{
	syncedInts.push_back(data);
}
void SyncedEntity::addSyncedData(syncedData<float>* data)
{
	this->syncedFloat.push_back(data);
}
void SyncedEntity::addSyncedData(syncedData<string>* data)
{
	this->syncedString.push_back(data);
}

void SyncedEntity::flagInt(int id)
{
	syncedInts.at(id)->flag = true;
}

void SyncedEntity::flagFloat(int id)
{
	syncedFloat.at(id)->flag = true;
}

void SyncedEntity::flagString(int id)
{
	syncedString.at(id)->flag = true;
}

void SyncedEntity::clearAllFlags()
{
	for (syncedData<int>* v : syncedInts)
	{
		v->flag = false;
	}
	for (syncedData<float>* v : syncedFloat)
	{
		v->flag = false;
	}
	for (syncedData<string>* v : syncedString)
	{
		v->flag = false;
	}
}
