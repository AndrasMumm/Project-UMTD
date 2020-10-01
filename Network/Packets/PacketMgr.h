#pragma once

#include "packet.h"

class PacketMgr
{
public:
	PacketMgr& getInstance()
	{
		static PacketMgr instance;
		return instance;
	}


private:
	PacketMgr() {}

public:
	void send(Packet& packet, int recipient = -1);
	void handle(Packet& packet, int sender);
};
