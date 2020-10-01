#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

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
	tcp::socket* socket;

	Client();
	~Client();
public:


};
