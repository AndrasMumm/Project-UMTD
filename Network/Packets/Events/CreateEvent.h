#pragma once
#include "../packet.h"
#include <iostream>

class CreateEventPacket : public Packet
{
public:
	int entityKey;
	int triggerTick;
	short eventID;
	std::vector<char> extraData;//Contains all event data, handles by the two big switch cases in GameEvent and EventCallbackHandler
	CreateEventPacket(const int entKey, const int eveID, const int tTick, std::vector<char>* eventData)
	{
		SetOpcode(EVENT_CREATE_OPCODE);
		entityKey = entKey;
		eventID = eveID;
		triggerTick = tTick;

		extraData.resize(eventData->size());
		memcpy(extraData.data(), eventData->data(), eventData->size());
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
			memcpy(extraData.data(), data.data() + 10, data.size() - 10);
		}
	}

	char* GetRaw(int* dataSize)
	{
		data.resize(10 + extraData.size());
		Put<int>(0, entityKey);
		Put<int>(4, triggerTick);
		Put<int>(8, eventID);
		memcpy(data.data() + 10, extraData.data(), extraData.size());
		return Packet::GetRaw(dataSize);
	}

};
