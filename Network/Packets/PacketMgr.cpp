#include "PacketMgr.h"
#include "../server.h"
#include "../client.h"

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
		Client::GetInstance().Send(packet);
	}
}

void PacketMgr::Handle(Packet* packet, int sender)
{
	std::cout << "Received packet with opcode " << packet->GetOpcode() << " from Participant " << sender << std::endl;
	packetQueue.push_back({ packet, sender });
}

void PacketMgr::Process()
{
	for (auto entry : packetQueue)
	{
		Packet* packet = entry.first;
		int sender = entry.second;
		auto opcode = packet->GetOpcode();
		auto handlers = callbacks.find(opcode);
		auto handlerCount = callbacks.count(opcode);
		for (int i = 0; i < handlerCount; ++i)
		{
			(*handlers->second)(packet, sender);
			handlers++;
		}

		//Cleanup
		delete packet;
	}

	packetQueue.clear();
}
