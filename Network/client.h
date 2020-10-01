#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "server.h"
#include "Packets/packet.h"

using namespace boost::asio;
using ip::tcp;
class Client
{
public:
	static Client& GetInstance()
	{
		static Client instance;
		return instance;
	}

private:
	//TCP Client
	io_service* _ioService;
	tcp::socket* _socket = nullptr;

	Client();
	~Client();
public:
	Packet* Read();
	void Send(Packet* packet);
	void Connect(std::string ip, int port = DEFAULT_GAME_PORT);
	void Disconnect() {};
};
