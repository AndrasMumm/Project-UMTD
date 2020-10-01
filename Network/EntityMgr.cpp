#include "EntityMgr.h"

SyncedEntity* EntityMgr::createSyncedEntity()
{
	syncedEntities.push_back(new SyncedEntity(++lastGivenEntityKey));
	return syncedEntities.back();
}

void EntityMgr::removeSyncedEntity(SyncedEntity* toBeRemoved)
{
	// ich weiﬂ hier w‰re ne hash map geil aber man habish kein bock 
	//das sollte mal wer testen
	syncedEntities.erase(std::find(syncedEntities.begin(),syncedEntities.end(),toBeRemoved));
	delete toBeRemoved;
}
