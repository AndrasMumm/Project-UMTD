#pragma once
#include <Network/SyncedEntity.h>
#include <Game\EventMgr.h>
#include <iostream>

class GameEntity : public SyncedEntity
{
public:
	GameEntity() : SyncedEntity(-1), eventManager(this) {};
	GameEntity(int entityKey) : SyncedEntity(entityKey), eventManager(this) {};
	EventMgr eventManager;
	void Update(int delta) override {
		std::cout << "U fcked up! GameEntity without Update function" << std::endl;
	}

	void ReceiveSync(SyncDataPacket* packet) override {

	}
};
