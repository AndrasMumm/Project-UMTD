#include "PacketMgr.h"
#include "../server.h"

PacketMgr::PacketMgr() {
}

void PacketMgr::RegisterCallback(short opcode, PacketHandlerFunction callback)
{
	callbacks.insert({ opcode, callback });
}

void PacketMgr::Send(Packet* packet, int recipient)
{
	if (Server::GetInstance().IsStarted())
	{
		//Sending it
		Server::GetInstance().Send(recipient, packet);
	}
	else
	{
		//We are client
	}
}

void PacketMgr::Handle(Packet* packet, int sender)
{
	auto opcode = packet->GetOpcode();
	std::cout << "Received packet with opcode " << opcode << " from Participant " << sender << std::endl;
	auto handlers = callbacks.find(opcode);
	auto handlerCount = callbacks.count(opcode);
	for (int i = 0; i < handlerCount; ++i)
	{
		(*handlers->second)(packet, sender);
		handlers++;
	}
}
