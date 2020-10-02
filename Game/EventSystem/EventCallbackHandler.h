#pragma once
#include <Network/Packets/PacketMgr.h>
class EventCallbackHandler
{
public:
	static void CreateHandler(Packet* p, int sender);
	static void DeleteHandler(Packet* p, int sender);
	static void Init();
};
