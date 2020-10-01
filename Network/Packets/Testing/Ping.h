#pragma once
#include "../packet.h"
#include <iostream>
#include <ctime>

class Ping : public Packet
{
private:
	std::string _msg;

	std::string GetRandomString(const int len) {

		std::string tmp_s;
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		srand((unsigned)std::time(NULL));

		for (int i = 0; i < len; ++i)
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


		return tmp_s;
	}

public:
	Ping() : Ping(GetRandomString(500))
	{
	}

	Ping(std::string msg)
	{
		SetOpcode(PING_OPCODE);
		_msg = msg;
	}

	Ping(Packet* p)
	{
		SetOpcode(PING_OPCODE);
		if (p->GetOpcode() != PING_OPCODE)
		{
			std::cout << "ERROR: Tried to create Ping packet from opcode " << p->GetOpcode() << std::endl;
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
