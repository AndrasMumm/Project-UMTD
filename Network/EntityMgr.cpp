#include "EntityMgr.h"

int EntityMgr::addSyncedEntity(SyncedEntity* t)
{
	syncedEntities.push_back(t);
	return ++(lastGivenEntityKey);
}

void EntityMgr::removeSyncedEntity(SyncedEntity* toBeRemoved)
{
	// ich weiß hier wäre ne hash map geil aber man habish kein bock 
	//das sollte mal wer testen
	syncedEntities.erase(std::find(syncedEntities.begin(), syncedEntities.end(), toBeRemoved));
}
