#include "EntityMgr.h"

SyncedEntity* EntityMgr::createSyncedEntity()
{
   syncedEntities.push_back(SyncedEntity(++lastGivenEntityKey));
   SyncedEntity& ret = syncedEntities.back();
   return &ret;
}

void EntityMgr::removeSyncedEntity(SyncedEntity* toBeRemoved)
{
	// ich weiﬂ hier w‰re ne hash map geil aber man habish kein bock 
	//das sollte mal wer testen
	syncedEntities.erase(syncedEntities.begin() + (toBeRemoved - &syncedEntities[0]));

}
