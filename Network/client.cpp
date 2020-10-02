#include "Client.h"
#include "Packets/Testing/Ping.h"
#include "Packets/Testing/Pong.h"

Client::Client()
{

}

Client::~Client()
{
	delete _ioService;
	delete _socket;
	delete serverHandleThread;
}

void Client::Connect(std::string ip, int port)
{
	if (_socket != nullptr)
	{
		std::cout << "ERROR: Already connected to a server!" << std::endl;
		return;
	}
	_ioService = new io_service();
	_socket = new tcp::socket(*_ioService);
	_socket->connect(tcp::endpoint(ip::address::from_string(ip), port));

	std::cout << "Connecting to " << ip << " on port " << port << std::endl;
	Ping ping = Ping();
	std::cout << "Sending Ping packet..." << std::endl;
	Send(&ping);

	Packet* p = Read();
	if (p->GetOpcode() == PONG_OPCODE)
	{
		Pong pong = Pong(p);
		if (pong.GetMsg() == ping.GetMsg())
		{
			std::cout << "Connection successful!" << std::endl;
		}
		else
		{
			std::cout << "ERROR: Pong packet contains different message than ping packet:" << std::endl
				<< "Ping message: " << ping.GetMsg() << std::endl
				<< "Pong message: " << pong.GetMsg() << std::endl;

			delete _socket;
			delete _ioService;
		}

	}
	else
	{
		std::cout << "ERROR: Did not receive Pong packet after Ping packet!" << std::endl;
		delete _socket;
		delete _ioService;
	}

	delete p;

	//Creating Handle thread
	serverHandleThread = new std::thread([&](Client* client) {
		client->HandleServerConnection();
		}, this);
}

void Client::HandleServerConnection()
{
	while (_socket != nullptr)
	{
		Packet* p = Read();
		PacketMgr::GetInstance().Handle(p, SERVER__ID);
	}
}

Packet* Client::Read()
{
	boost::asio::streambuf buf;
	boost::asio::read_until(*_socket, buf, char(PACKET_DELIMTER));
	int dataSize = buf.size() - 1; //-1 because of delimiter
	Packet* packet = new Packet(boost::asio::buffer_cast<const char*>(buf.data()), dataSize);
	return packet;
}

void Client::Send(Packet* packet)
{
	int dSize = 0;
	char* data = packet->GetRaw(&dSize);
	boost::asio::write(*_socket, boost::asio::buffer(data, dSize));
	//Delimiter
	char delimiter = PACKET_DELIMTER;
	boost::asio::write(*_socket, boost::asio::buffer(&delimiter, 1));

	delete[] data;
}
