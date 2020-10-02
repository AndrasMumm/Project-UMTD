#include "EntityMgr.h"


int EntityMgr::getNextEntityKey()
{
	return ++lastGivenEntityKey;
}
void EntityMgr::addSyncedEntity(SyncedEntity* t)
{
	int entityKey = t->entityKey;
	syncedEntities.insert({ entityKey, t });
}

void EntityMgr::removeSyncedEntity(SyncedEntity* toBeRemoved)
{
	syncedEntities.erase(toBeRemoved->entityKey);
}

SyncedEntity* EntityMgr::getSyncedEntity(int entityKey)
{
	return syncedEntities.at(entityKey);
}
