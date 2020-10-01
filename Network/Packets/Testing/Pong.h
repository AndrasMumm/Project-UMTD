#pragma once
#include "Ping.h"
class Pong : Packet
{
	Pong(std::string msg)
	{
		const char* msgData = msg.c_str();
		data.resize(msg.size());
		memcpy(data.data(), msgData, msg.size());
	}
};
