#include "EntityMgr.h"

int EntityMgr::addSyncedEntity(SyncedEntity* t)
{
	int entityKey = ++lastGivenEntityKey;
	syncedEntities.insert({ entityKey, t });
	return entityKey;
}

void EntityMgr::removeSyncedEntity(SyncedEntity* toBeRemoved)
{
	syncedEntities.erase(toBeRemoved->entityKey);
}

SyncedEntity* EntityMgr::getSyncedEntity(int entityKey)
{
	return syncedEntities.at(entityKey);
}
