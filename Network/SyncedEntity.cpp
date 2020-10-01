#include "SyncedEntity.h"

using namespace std;


SyncedEntity::SyncedEntity(int entityKey) :entityKey(entityKey)
{
}

int* SyncedEntity::addSyncedData(syncedData<int>& data)
{
	syncedInts.push_back(data);
	return &(syncedInts.back().value);
}
float* SyncedEntity::addSyncedData(syncedData<float>& data)
{
	this->syncedFloat.push_back(data);
	return &(syncedFloat.back().value);
}
string* SyncedEntity::addSyncedData(syncedData<string>& data)
{
	this->syncedString.push_back(data);
	return &(syncedString.back().value);
}

void SyncedEntity::flagInt(int id)
{
	syncedInts.at(id).flag = true;
}

void SyncedEntity::flagFloat(int id)
{
	syncedFloat.at(id).flag = true;
}

void SyncedEntity::flagString(int id)
{
	syncedString.at(id).flag = true;
}

void SyncedEntity::clearAllFlags()
{
	for (syncedData<int> v : syncedInts)
	{
		v.flag = false;
	}
	for (syncedData<float> v : syncedFloat)
	{
		v.flag = false;
	}
	for (syncedData<string> v : syncedString)
	{
		v.flag = false;
	}
}
