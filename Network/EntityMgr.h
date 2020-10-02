#pragma once

#include <vector>
#include <Network/SyncedEntity.h>
#include <unordered_map>

class EntityMgr
{
public:
	static EntityMgr& getInstance()
	{
		static EntityMgr instance;

		return instance;
	}
private:
	EntityMgr() {}



	int lastGivenEntityKey = 100;

	std::unordered_map<int, SyncedEntity*> syncedEntities;


public:
	EntityMgr(EntityMgr const&) = delete;
	void operator=(EntityMgr const&) = delete;

	int getNextEntityKey();
	void addSyncedEntity(SyncedEntity* toAdd);
	void removeSyncedEntity(SyncedEntity* toBeRemoved);

	SyncedEntity* getSyncedEntity(int entityKey);
};
