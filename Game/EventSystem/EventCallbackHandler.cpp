#include "EventCallbackHandler.h"
#include <Network/Packets/Events/CreateEvent.h>
#include "../Entities/gameentity.h"
#include <Network\EntityMgr.h>

void EventCallbackHandler::CreateHandler(Packet* p, int sender)
{
	CreateEventPacket packet = CreateEventPacket(p);
	int entityKey = packet.entityKey;

	SyncedEntity* se = EntityMgr::getInstance().getSyncedEntity(entityKey);
	GameEntity* ge = (GameEntity*)se;
}
void EventCallbackHandler::DeleteHandler(Packet* p, int sender)
{
}

void EventCallbackHandler::Init()
{
	PacketMgr::GetInstance().RegisterCallback(EVENT_CREATE_OPCODE, &EventCallbackHandler::CreateHandler);
	PacketMgr::GetInstance().RegisterCallback(EVENT_DELETE_OPCODE, &EventCallbackHandler::DeleteHandler);
}
