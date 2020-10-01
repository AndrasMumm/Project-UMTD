#pragma once
#include "../packet.h"
#include <iostream>

class CreateEventPacket : public Packet
{
private:

public:
	int entityKey;
	int triggerTick;
	short eventID;
	CreateEventPacket(int entKey, int eveID, int tTick)
	{
		SetOpcode(EVENT_CREATE_OPCODE);
		entityKey = entKey;
		eventID = eveID;
		triggerTick = tTick;
	}

	CreateEventPacket(Packet* p)
	{
		SetOpcode(EVENT_CREATE_OPCODE);
		if (p->GetOpcode() != EVENT_CREATE_OPCODE)
		{
			std::cout << "ERROR: Tried to create CreateEventPacket packet from opcode " << p->GetOpcode() << std::endl;
			data.resize(0);
		}
		else
		{
			entityKey = p->Read<int>(0);
			triggerTick = p->Read<int>(4);
			eventID = p->Read<int>(8);
		}
	}

	char* GetRaw(int* dataSize)
	{
		data.resize(10);
		Put<int>(0, entityKey);
		Put<int>(4, triggerTick);
		Put<int>(8, eventID);
		return Packet::GetRaw(dataSize);
	}

};
