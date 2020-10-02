#include "EventCallbackHandler.h"
#include <Network/Packets/Events/CreateEvent.h>
#include "../Entities/gameentity.h"
#include <Network\EntityMgr.h>
#include "HelperAllEvents.h"

template <class T>
T Read(std::vector<char>* v, int index)
{
	return *(((T*)v) + index);
};

CreateEnemyEvent* CreateCreateEnemyEvent(CreateEventPacket* packet)
{
	std::vector<char>* extraData = &packet->extraData;
	int enemyEntityKey = Read<int>(extraData, 0);
	short enemyID = Read<short>(extraData, 4);
	int level = Read<int>(extraData, 6);
	float posX = Read<float>(extraData, 10);
	float posY = Read<float>(extraData, 14);
	return  new CreateEnemyEvent(packet->triggerTick, enemyEntityKey, enemyID, level, posX, posY);
}

void EventCallbackHandler::CreateHandler(Packet* p, int sender)
{
	CreateEventPacket packet = CreateEventPacket(p);
	int ownerEntityKey = packet.ownerEntityKey;

	GameEntity* ge = (GameEntity*)EntityMgr::getInstance().getSyncedEntity(ownerEntityKey);

	GameEvent* gameEvent;
	switch (packet.eventID)
	{
	case CREATE_ENEMY_EVENT_ID:
		gameEvent = CreateCreateEnemyEvent(&packet);
		break;
	default:
		gameEvent = nullptr;
		break;
	}

	ge->eventManager.AddEvent(gameEvent);
}
void EventCallbackHandler::DeleteHandler(Packet* p, int sender)
{
}

void EventCallbackHandler::Init()
{
	PacketMgr::GetInstance().RegisterCallback(EVENT_CREATE_OPCODE, &EventCallbackHandler::CreateHandler);
	PacketMgr::GetInstance().RegisterCallback(EVENT_DELETE_OPCODE, &EventCallbackHandler::DeleteHandler);
}
