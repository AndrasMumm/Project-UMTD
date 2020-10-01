#pragma once

#include <vector>
#include <Network/SyncedEntity.h>

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
   
    std::vector<SyncedEntity*> syncedEntities;


public:
    EntityMgr(EntityMgr const&) = delete;
    void operator=(EntityMgr const&) = delete;

    SyncedEntity* createSyncedEntity();
    void removeSyncedEntity(SyncedEntity* toBeRemoved);
};