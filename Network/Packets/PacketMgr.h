#pragma once

#include "packet.h"
#include <map>

typedef void (*PacketHandlerFunction)(Packet*, int);
class PacketMgr
{
public:
	static PacketMgr& GetInstance()
	{
		static PacketMgr instance;
		return instance;
	}

private:
	PacketMgr();
	std::vector<std::pair<Packet*, int>> packetQueue;
	std::multimap<short, PacketHandlerFunction> callbacks;
public:
	void RegisterCallback(short opcode, PacketHandlerFunction callback);
	void Send(Packet* packet, int recipient = -1);
	void Handle(Packet* packet, int sender);
	void Process();
};
