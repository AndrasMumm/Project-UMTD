#include "PacketMgr.h"
#include "../server.h"

PacketMgr::PacketMgr() {
}

void PacketMgr::RegisterCallback(short opcode, PacketHandlerFunction callback)
{
	callbacks.insert({ opcode, callback });
}

void PacketMgr::Send(Packet& packet, int recipient)
{
	if (Server::GetInstance().IsStarted())
	{
		//We are host
		auto rec = Server::GetInstance().GetParticipant(recipient);

		//Building the packet
		int dSize = 0;
		char* d = packet.GetRaw(&dSize);

		//Sending it
		Server::GetInstance().SendOverSocket(rec->socket, d, dSize);

		//Clean up
		delete[] d;
	}
	else
	{
		//We are client
	}
}

void PacketMgr::Handle(Packet& packet, int sender)
{
	auto opcode = packet.GetOpcode();
	std::cout << "Received packet with opcode " << opcode << " from Participant " << sender << std::endl;
	auto handlers = callbacks.find(opcode);
	auto handlerCount = callbacks.count(opcode);
	for (int i = 0; i < handlerCount; ++i)
	{
		(*handlers->second)(packet, sender);
		handlers++;
	}
}
