#pragma once
#include <Network/SyncedEntity.h>
#include <Game\EventMgr.h>
#include <iostream>

class GameEntity : public SyncedEntity
{
public:

	GameEntity() : SyncedEntity(-1) {}
	EventMgr eventManager;
	void Update(int delta) override {
		std::cout << "U fcked up! GameEntity without Update function" << std::endl;
	}
};
