#pragma once
#include "../packet.h"
#include <iostream>

class Pong : public Packet
{
private:
	std::string _msg;
public:
	Pong(std::string msg)
	{
		_msg = msg;
		SetOpcode(PONG_OPCODE);
	}

	Pong(Packet* p)
	{
		SetOpcode(PONG_OPCODE);
		if (p->GetOpcode() != PONG_OPCODE)
		{
			std::cout << "ERROR: Tried to create Pong packet from opcode " << p->GetOpcode() << std::endl;
			_msg = "";
		}
		else
		{
			_msg = std::string(p->data.data(), p->data.size());
		}
	}

	std::string GetMsg()
	{
		return _msg;
	}

	char* GetRaw(int* dataSize)
	{
		const char* msgData = _msg.c_str();
		data.resize(_msg.size());
		memcpy(data.data(), msgData, _msg.size());
		return Packet::GetRaw(dataSize);
	}
};
