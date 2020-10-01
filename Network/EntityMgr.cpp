#include "EntityMgr.h"

SyncedEntity* EntityMgr::createSyncedEntity()
{
   syncedEntities.push_back(SyncedEntity(++lastGivenEntityKey));
   SyncedEntity& ret = syncedEntities.back();
   return &ret;
}
