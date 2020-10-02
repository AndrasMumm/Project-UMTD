#pragma once
#include "../packet.h"
#include <iostream>

class CreateEventPacket : public Packet
{
public:
	int ownerEntityKey;
	int triggerTick;
	short eventID;
	//Contains all event data, handles by the two big switch cases in GameEvent::SendToAll and the EventCallbackHandler handler
	std::vector<char> extraData;

	CreateEventPacket(const int ownerEntKey, const short eveID, const int tTick, std::vector<char>* eventData)
	{
		SetOpcode(EVENT_CREATE_OPCODE);
		ownerEntityKey = ownerEntKey;
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
			ownerEntityKey = p->Read<int>(0);
			triggerTick = p->Read<int>(4);
			eventID = p->Read<short>(8);
			extraData.resize(data.size() - 10);
			memcpy(extraData.data(), data.data() + 10, data.size() - 10);
		}
	}

	char* GetRaw(int* dataSize)
	{
		data.resize(10 + extraData.size());
		Put<int>(0, ownerEntityKey);
		Put<int>(4, triggerTick);
		Put<short>(8, eventID);
		memcpy(data.data() + 10, extraData.data(), extraData.size());
		return Packet::GetRaw(dataSize);
	}

};
