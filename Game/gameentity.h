﻿#pragma once
#include <Network/SyncedEntity.h>
#include <Game\EventMgr.h>

class GameEntity : public SyncedEntity
{
public:
	EventMgr eventManager;
};
