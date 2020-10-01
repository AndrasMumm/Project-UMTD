#pragma once
#include "../packet.h"

#include <iostream>
#include <ctime>

class Ping : Packet
{
private:
	std::string msg;

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
	Ping()
	{
		SetOpcode(9);
		msg = GetRandomString(500);
	}

	char* GetRaw(int* dataSize)
	{
		const char* msgData = msg.c_str();
		data.resize(msg.size());
		memcpy(data.data(), msgData, msg.size());
		return Packet::GetRaw(dataSize);
	}
};
