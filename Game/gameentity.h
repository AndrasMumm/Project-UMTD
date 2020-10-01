#pragma once
#include <Network/SyncedEntity.h>
#include <Game\EventMgr.h>

class GameEntity : public SyncedEntity
{
	EventMgr eventManager;
};
